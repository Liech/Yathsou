#include "Core/Connection.h"

#include <cassert>
#include <stdexcept>
#include <chrono>
#include <thread>
#include <iostream>


namespace Vishala {
  Connection::Connection() {
    setChannelCount(1);
    if (numberOfConnectsions == 0)
      enet_initialize();
    numberOfConnectsions++;
  }
   
  Connection::~Connection() {
    _destructorCalled = true;
    if (_thread.valid())
      _thread.wait();
    numberOfConnectsions--;
    if (numberOfConnectsions == 0)
      enet_deinitialize();
    if (_connection != nullptr) {
      enet_host_destroy(_connection);
    }
  }

  bool Connection::start() {
    assert(_connection == nullptr);
    std::cout << "Connection::start() with port " << _port << std::endl;
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
      return false;
    _thread = std::async(std::launch::async, [this]() {threadRun(); });
    return true;
  }

  void Connection::connectionFailed(std::string ip, int port) {
    NetReciveEvent newCon;
    newCon.newConnection     = true;
    newCon.connectionSuccess = false;
    newCon.targetIP          = ip;
    newCon.port              = port;
    _threadQueueRecive.enqueue(newCon);
  }

  void Connection::threadRun() {
    while (!_destructorCalled) {
      NetSendEvent toSend;
      if (_threadQueueSend.try_dequeue(toSend)) {
        if (toSend.type == NetSendEvent::Type::send) {
          ENetPacket* packet = enet_packet_create(toSend.data.data(), toSend.data.size(), toSend.reliable ? ENET_PACKET_FLAG_RELIABLE : 0);
          enet_peer_send(_peers[toSend.target], toSend.channel, packet);
        }
        else if (toSend.type == NetSendEvent::Type::connectNonblock) {
          ENetAddress address;
          enet_address_set_host(&address, toSend.ip.c_str());
          address.port = toSend.port;
          ENetPeer* peer = nullptr;
          peer = enet_host_connect(_connection, &address, _numberOfChannels, 0);
          if (peer == NULL)
            connectionFailed(toSend.ip, toSend.port);
          ToBePeer p;
          p.peer            = peer                            ;
          p.connectionStart = std::chrono::steady_clock::now();
          {
            std::lock_guard<std::mutex> guard(_toBePeersLock);
            _toBePeers.push_back(p);
          }
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
            _currentlyConnecting = true;
            bool connectionAttemptSuccessful = enet_host_service(_connection, &event, 5000) > 0;
            _currentlyConnecting = false;
            if (connectionAttemptSuccessful && event.type == ENET_EVENT_TYPE_CONNECT)
            {
              NetReciveEvent newCon;
              newCon.newConnection      = true              ;
              newCon.connectionSuccess  = true              ;
              newCon.targetIP           = toSend.ip         ;
              newCon.player             = _clientNameCounter;
              newCon.port               = peer->address.port;
              //_threadQueueRecive.enqueue(newCon);
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
              newCon.port     = toSend.port;
              _threadQueueRecive.enqueue(newCon);
              continue;
            }
          }
          else {
            connectionFailed(toSend.ip,toSend.port);
          }
        }
        else {
          for (auto p : _peers)
            enet_peer_disconnect(p.second, 0);
        }
      }
      if (_destructorCalled)
        return;
      ENetEvent event;
      if (_connection && enet_host_service(_connection, &event, 0) > 0) {
        NetReciveEvent msg;
        msg.type = event.type;
        msg.channel = event.channelID;
        switch (event.type)
        {
        case ENetEventType::ENET_EVENT_TYPE_CONNECT:
        {
          event.peer->data = (void*)_clientNameCounter;
          _peers[_clientNameCounter] = event.peer;
          msg.player    = _clientNameCounter;
          
          char* buffer = new char[256];          
          int len = enet_address_get_host_ip(&event.peer->address, buffer, 256);
          msg.port = event.peer->address.port;
          msg.targetIP = std::string(buffer);
          delete[] buffer;
          
          {
            std::lock_guard<std::mutex> guard(_toBePeersLock);
            for (int i = 0; i < _toBePeers.size(); i++) {
              if (_toBePeers[i].peer == event.peer) {
                _toBePeers.erase(_toBePeers.begin() + i);
                break;
              }
            }
          }

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
          std::cout << "DC!"<<std::endl;
        }
        }
        _threadQueueRecive.enqueue(msg);
      }
    }
  }

  void Connection::stop() {
    assert(_connection != nullptr);
    std::cout << "CONNECTION STOP" << std::endl;
    NetSendEvent toSend;
    toSend.type     = NetSendEvent::Type::disconnect;
    _threadQueueSend.enqueue(toSend);

    _thread.wait_until(std::chrono::system_clock::now() + std::chrono::seconds(1));
    while (_currentlyConnecting) 
      std::this_thread::sleep_for(std::chrono::seconds(10));    
    for (auto p : _peers)
      enet_peer_reset(p.second);

    enet_host_destroy(_connection);
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
          std::cout << "NewConFailed!" << std::endl;
          _connectionFailed(event.targetIP, event.port);
          return;
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
          std::cout << "DC!" << std::endl;
          _disconnect(event.player);
          return;
        }
        }
      }
    }

    std::lock_guard<std::mutex> guard(_toBePeersLock);
    for (int i = _toBePeers.size() - 1;i >= 0; i--) {
      auto now = std::chrono::steady_clock::now();
      int timePassed = std::chrono::duration_cast<std::chrono::milliseconds>(now - _toBePeers[i].connectionStart).count();
      
      if (timePassed > 5000) {        
        char*       buffer = new char[256];
        int         len = enet_address_get_host_ip(&_toBePeers[i].peer->address, buffer, 256);
        int         port = _toBePeers[i].peer->address.port;
        std::string ip = std::string(buffer);
        delete[] buffer;
        _connectionFailed(ip, port);
        _toBePeers.erase(_toBePeers.begin() + i);
      }
    }
  }
   
  void Connection::connect(int port, std::string ip) {
    NetSendEvent toSend;
    toSend.type = NetSendEvent::Type::connect;
    toSend.ip = ip;
    toSend.port = port;
    _threadQueueSend.enqueue(toSend);
  }

  void Connection::connectNonblocking(int port, std::string ip) {
    NetSendEvent toSend;
    toSend.type = NetSendEvent::Type::connectNonblock;
    toSend.ip = ip;
    toSend.port = port;
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

  void Connection::setConnectionFailedCallback(std::function<void(std::string ip, int port)> func) {
    _connectionFailed = func;
  }

  std::vector<size_t> Connection::getAllConnections() {
    std::vector<size_t> result;
    for (auto peer : _peers) {
      result.push_back(peer.first);
    }
    return result;
  }

}