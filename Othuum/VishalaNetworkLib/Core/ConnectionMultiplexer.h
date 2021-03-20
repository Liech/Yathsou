#pragma once

#include <memory>
#include <functional>
#include <map>
#include "VishalaNetworkLib/Core/BinaryPackage.h"

namespace Vishala {
  class Connection;
  class BinaryPackage;

  class ConnectionMultiplexer {
  public:
    ConnectionMultiplexer(uint8_t channel, std::shared_ptr<Connection>);
    std::shared_ptr<Connection> connection();
    void setOnRecievedCall(size_t clientNumber, std::function<void(std::unique_ptr<BinaryPackage>)>);

  private:
    std::map<size_t, std::function<void(std::unique_ptr<BinaryPackage>)>> _callbackMap;
    std::shared_ptr<Connection>                                           _connection;
    uint8_t                                                               _channel;
  };
}