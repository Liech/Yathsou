#include "Connection.h"

#include <cassert>
#include <stdexcept>

namespace Vishala {
  Connection::Connection() {
    
  }

  Connection::~Connection() {
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
        event.peer->data = (void*)_clientNameCounter;
        _newConnection(*((size_t*)event.peer->data));
        _clientNameCounter++;
        break;
      case ENetEventType::ENET_EVENT_TYPE_RECEIVE:
        _recived[event.channelID]((size_t)event.peer->data, event.packet->data, event.packet->dataLength);
        enet_packet_destroy(event.packet);
        break;

      case ENetEventType::ENET_EVENT_TYPE_DISCONNECT:
        _disconnect((size_t)event.peer->data);
        event.peer->data = NULL;
      }
    }
  }

  void Connection::setChannelCount(size_t numberOfChannels) {
    assert(_connection == nullptr);
    _numberOfChannels = numberOfChannels;
    _recived.resize(numberOfChannels);
    for (size_t i = 0; i < _numberOfChannels; i++)
      _recived[i] = [](size_t  clientNumber, uint8_t* package, size_t length) {};
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

  void Connection::setRecievedCallback(size_t channel, std::function<void(size_t  clientNumber, uint8_t* package, size_t length)> func) {
    assert(_connection == nullptr);
    _recived[channel] = func;
  }
}