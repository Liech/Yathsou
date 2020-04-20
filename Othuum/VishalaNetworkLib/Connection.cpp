#include "Connection.h"

#include <cassert>
#include <stdexcept>
#include <chrono>
#include <thread>

#include "BinaryPackage.h"

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
      delete _connection;
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
  }

  void Connection::stop() {
    assert(_connection != nullptr);
    for (auto p : _peers)
      enet_peer_disconnect(p.second, 0);

    std::this_thread::sleep_for(std::chrono::milliseconds(3000));

    for (auto p : _peers)
      enet_peer_reset(p.second);

    enet_host_destroy(_connection);
    delete _connection;
    _connection = nullptr;
  }

  void Connection::update() {
    ENetEvent event;
    while (enet_host_service(_connection, &event, 0) > 0) {
      switch (event.type)
      {
      case ENetEventType::ENET_EVENT_TYPE_CONNECT:
      {
        event.peer->data = (void*)_clientNameCounter;
        _peers[_clientNameCounter] = event.peer;
        _newConnection(*((size_t*)event.peer->data));
        _clientNameCounter++;
        break;
      }
      case ENetEventType::ENET_EVENT_TYPE_RECEIVE:
      {
        std::unique_ptr< BinaryPackage > package = std::make_unique<BinaryPackage>();
        //package->writeBinary((unsigned char*)event.packet->data, event.packet->dataLength);
        //package->startRead();
        _recived[event.channelID]((size_t)event.peer->data, std::move(package));
        enet_packet_destroy(event.packet);
        break;
      }
      case ENetEventType::ENET_EVENT_TYPE_DISCONNECT:
      {
        _disconnect((size_t)event.peer->data);
        _peers.erase((size_t)event.peer->data);
        event.peer->data = NULL;
      }
      }
    }
  }

  size_t Connection::connect(int port, std::string ip) {
    ENetAddress address;
    enet_address_set_host(&address, ip.c_str());
    address.port = port;
    ENetPeer* peer = nullptr;
    peer = enet_host_connect(_connection, &address, _numberOfChannels, 0);
    if (peer == NULL)
      return 18446744073709551615;
    ENetEvent event;
    if (enet_host_service(_connection, &event, 5000) > 0 && event.type == ENET_EVENT_TYPE_CONNECT)
    {
      _newConnection(_clientNameCounter);
      _peers[_clientNameCounter] = peer;
      peer->data = (void*)_clientNameCounter;
      _clientNameCounter++;
      return _clientNameCounter-1;
    }
    else {
      enet_peer_reset(peer);
      return 18446744073709551615;
    }    
  }

  void Connection::send(size_t target,uint8_t channel, std::unique_ptr< BinaryPackage > package, bool reliable) {
    ENetPacket* packet = enet_packet_create(package->getBinary().data(), package->getBinary().size(), reliable?ENET_PACKET_FLAG_RELIABLE:0);
    enet_peer_send(_peers[target], channel, packet);
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

  void Connection::setNewConnectionCallback(std::function<void(size_t clientnumber)> func) {
    assert(_connection == nullptr);
    _newConnection = func;
  }

  void Connection::setDisconnectCallback(std::function<void(size_t clientnumber)> func) {
    assert(_connection == nullptr);
    _disconnect = func;
  }

  void Connection::setRecievedCallback(uint8_t channel, std::function<void(size_t  clientNumber, std::unique_ptr< BinaryPackage > package)> func) {
    assert(_connection == nullptr);
    _recived[channel] = func;
  }
}