#include "ConnectionMultiplexer.h"

#include "Connection.h"

namespace Vishala {
  ConnectionMultiplexer::ConnectionMultiplexer(uint8_t channel, std::shared_ptr<Connection> con) {
    _channel = channel;
    _connection = con;

    _connection->setRecievedCallback(channel, [this](size_t clientNumber, std::unique_ptr<Vishala::BinaryPackage> package) {
      if (_callbackMap.count(clientNumber) == 0)
        return;
      _callbackMap[clientNumber](std::move(package));
      });
  }

  std::shared_ptr<Connection> ConnectionMultiplexer::connection() {
    return _connection;
  }

  void ConnectionMultiplexer::setOnRecievedCall(size_t clientNumber, std::function<void(std::unique_ptr<BinaryPackage>)> callback) {
    _callbackMap[clientNumber] = callback;
  }

}