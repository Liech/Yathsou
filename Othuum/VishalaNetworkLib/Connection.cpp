#include "Connection.h"

#include <cassert>
#include <stdexcept>
#include <chrono>
#include <thread>


namespace Vishala {
  Connection::Connection() {
    setChannelCount(1);
    if (numberOfConnectsions == 0)
      enet_initialize();
    numberOfConnectsions++;
  }

  Connection::~Connection() {
    numberOfConnectsions--;
    if (numberOfConnectsions == 0)
      enet_deinitialize();
    if (_connection != nullptr) {
      enet_host_destroy(_connection);
    }
  }

  void Connection::start() {
    assert(_connection == nullptr);
    if (_acceptsConnections) {
      ENetAddress address;
      address.host = ENET_HOST_ANY;
      address.port = _port;
      _connection = enet_host_create(&address, _numberOfConnections, _numberOfChannels, 0, 0);
    }
    else {
      _connection = enet_host_create(nullptr,_numberOfConnections,_numberOfChannels,0,0);
    }
    if (_connection == NULL)
      throw std::runtime_error("Error Creating Host");
    _thread = std::async(std::launch::async, [this]() {threadRun(); });
  }

  void Connection::threadRun() {
    while (true) {
      NetSendEvent toSend;
      if (_threadQueueSend.try_dequeue(toSend)) {
        if (toSend.type == NetSendEvent::Type::send) {
          ENetPacket* packet = enet_packet_create(toSend.data.data(), toSend.data.size(), toSend.reliable ? ENET_PACKET_FLAG_RELIABLE : 0);
          enet_peer_send(_peers[toSend.target], toSend.channel, packet);
        }
        else if (toSend.type == NetSendEvent::Type::connect) {
          ENetAddress address;
          enet_address_set_host(&address, toSend.ip.c_str());
          address.port = toSend.port;
          ENetPeer* peer = nullptr;
          peer = enet_host_connect(_connection, &address, _numberOfChannels, 0);
          if (peer != NULL)
          {
            ENetEvent event;
            if (enet_host_service(_connection, &event, 5000) > 0 && event.type == ENET_EVENT_TYPE_CONNECT)
            {
              NetReciveEvent newCon;
              newCon.newConnection      = true              ;
              newCon.connectionSuccess  = true              ;
              newCon.targetIP           = toSend.ip         ;
              newCon.player             = _clientNameCounter;
              newCon.port               = peer->address.port;
              _threadQueueRecive.enqueue(newCon);
              _peers[_clientNameCounter] = peer;
              peer->data = (void*)_clientNameCounter;
              _clientNameCounter++;
            }
            else {
              enet_peer_reset(peer);
              NetReciveEvent newCon;
              newCon.newConnection = true;
              newCon.connectionSuccess = false;
              newCon.targetIP = toSend.ip;
              _threadQueueRecive.enqueue(newCon);
              continue;
            }
          }
          else {
            NetReciveEvent newCon;
            newCon.newConnection     = true              ;
            newCon.connectionSuccess = false             ;
            newCon.targetIP          = toSend.ip         ;
            newCon.port              = peer->address.port;
            _threadQueueRecive.enqueue(newCon);
          }
        }
        else {
          for (auto p : _peers)
            enet_peer_disconnect(p.second, 0);
        }
      }

      ENetEvent event;
      if (enet_host_service(_connection, &event, 0) > 0) {
        NetReciveEvent msg;
        msg.type = event.type;
        msg.channel = event.channelID;
        switch (event.type)
        {
        case ENetEventType::ENET_EVENT_TYPE_CONNECT:
        {
          event.peer->data = (void*)_clientNameCounter;
          _peers[_clientNameCounter] = event.peer;
          msg.player = _clientNameCounter;
          _clientNameCounter++;
          break;
        }
        case ENetEventType::ENET_EVENT_TYPE_RECEIVE:
        {
          msg.data = std::vector<unsigned char>(event.packet->data, event.packet->data + event.packet->dataLength);
          msg.player = (size_t)event.peer->data;
          enet_packet_destroy(event.packet);
          break;
        }
        case ENetEventType::ENET_EVENT_TYPE_DISCONNECT:
        {
          msg.player = (size_t)event.peer->data;
          event.peer->data = NULL;
          _peers.erase((size_t)event.peer->data);
        }
        }
        _threadQueueRecive.enqueue(msg);
      }
    }
  }

  void Connection::stop() {
    assert(_connection != nullptr);

    NetSendEvent toSend;
    toSend.type     = NetSendEvent::Type::disconnect;
    _threadQueueSend.enqueue(toSend);

    std::this_thread::sleep_for(std::chrono::milliseconds(3000));

    for (auto p : _peers)
      enet_peer_reset(p.second);

    enet_host_destroy(_connection);
    delete _connection;
    _connection = nullptr;
  }

  void Connection::update() {
    assert(_connection != nullptr, "start() not called");
    NetReciveEvent event;
    while (_threadQueueRecive.try_dequeue(event)) {
      if (event.newConnection) {
        if (event.connectionSuccess) {
          _newConnection(event.player, event.targetIP, event.port);
        }
        else {
          _connectionFailed(event.targetIP);
        }
      }
      else {
        switch (event.type)
        {
        case ENetEventType::ENET_EVENT_TYPE_CONNECT:
        {
          _newConnection(event.player, event.targetIP,event.port);
          break;
        }
        case ENetEventType::ENET_EVENT_TYPE_RECEIVE:
        {
          std::unique_ptr< BinaryPackage > package = std::make_unique<BinaryPackage>();
          package->data = event.data;
          _recived[event.channel](event.player, std::move(package));
          break;
        }
        case ENetEventType::ENET_EVENT_TYPE_DISCONNECT:
        {
          _disconnect(event.player);
        }
        }
      }
    }
  }

  void Connection::connect(int port, std::string ip) {
    NetSendEvent toSend;
    toSend.type     = NetSendEvent::Type::connect;
    toSend.ip       = ip                         ;
    toSend.port     = port                       ;
    _threadQueueSend.enqueue(toSend);
  }

  void Connection::send(size_t target,uint8_t channel, std::unique_ptr< BinaryPackage > package, bool reliable) {
    NetSendEvent toSend;
    toSend.channel  = channel                 ;
    toSend.target   = target                  ;
    toSend.reliable = reliable                ;
    toSend.type     = NetSendEvent::Type::send;
    toSend.data     = package->data           ;
    _threadQueueSend.enqueue(toSend);
  }

  void Connection::setChannelCount(uint8_t numberOfChannels) {
    assert(_connection == nullptr);
    _numberOfChannels = numberOfChannels;
    _recived.resize(numberOfChannels);
    for (size_t i = 0; i < _numberOfChannels; i++)
      _recived[i] = [](size_t  clientNumber, std::unique_ptr< BinaryPackage > package) {};
  }

  void Connection::setMaximumConnectionCount(size_t max) {
    assert(_connection == nullptr);
    _numberOfConnections = max;
  }

  void Connection::setAcceptConnection(bool accept) {
    assert(_connection == nullptr);
    _acceptsConnections = accept;
  }

  void Connection::setPort(int port) {
    assert(_connection == nullptr);
    _port = port;
  }

  void Connection::setNewConnectionCallback(std::function<void(size_t clientnumber, std::string ip, int port)> func) {
    _newConnection = func;
  }

  void Connection::setDisconnectCallback(std::function<void(size_t clientnumber)> func) {
    _disconnect = func;
  }

  void Connection::setRecievedCallback(uint8_t channel, std::function<void(size_t  clientNumber, std::unique_ptr< BinaryPackage > package)> func) {
    _recived[channel] = func;
  }

  void Connection::setConnectionFailedCallback(std::function<void(std::string ip)> func) {
    _connectionFailed = func;
  }
}