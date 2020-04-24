#include "Protocoll.h"

#include "Connection.h"

#include <cassert>

namespace Vishala {
  Protocoll::Protocoll() {
  }
  
  Protocoll::Protocoll(std::function<void(std::shared_ptr<Protocoll>)> nextProtocollInvoked, std::unique_ptr<Connection> connection) {
    init(nextProtocollInvoked, std::move(connection));
  }

  bool Protocoll::isActive() {
    return (_connection != nullptr);
  }

  void Protocoll::update() {
    assert(isActive());
    _connection->update();
  }

  void Protocoll::sendMessage(size_t player, size_t channel, std::unique_ptr<BinaryPackage> package) {
    assert(isActive());
    _connection->send(player, channel, std::move(package));
  }

  void Protocoll::connect(int port, std::string ip) {
    assert(isActive());
    _connection->connect(port, ip);
  }

  void Protocoll::handOver(std::shared_ptr<Protocoll> next) {
    if (next != nullptr) {
      next->init(_next, std::move(_connection));
      _connection = nullptr;
      next->_next(next);
    }
    else {
      _next(nullptr);
    }
  }

  void Protocoll::init(std::function<void(std::shared_ptr<Protocoll>)> nextProtocollInvoked, std::unique_ptr<Connection> connection) {
    _next = nextProtocollInvoked;
    if (connection != nullptr) {
      _connection = std::move(connection);
      _connection->setConnectionFailedCallback([this](std::string name) {connectionFailed(name); });
      _connection->setDisconnectCallback      ([this](size_t player)    {disconnect(player);     });
      _connection->setNewConnectionCallback   ([this](size_t player)    {newConnection(player);  });
      for (size_t i = 0; i < _connection->getChannelCount(); i++)
        _connection->setRecievedCallback(i, [this,i](size_t  clientNumber, std::unique_ptr< BinaryPackage > package) {messageRecived(clientNumber, i,std::move(package)); });
    }
  }
}