#pragma once

#include <memory>
#include <functional>
#include "VishalaNetworkLib/Core/Command.h"

namespace Iyathuum {
  class UpdateTimer;
}

namespace Vishala {
  class Serialization;
  class Connection;
  class BinaryPackage;
  class NetworkMemoryWriter;

  class AuthoritarianGameServer {
  public:
    AuthoritarianGameServer(std::unique_ptr<Serialization> data,int port, int ticksPerSecond);
    void addOnUpdate(std::unique_ptr<ICommand>);
    void update();
    
  private:
    void initConnection(int port);
    void nextTick();
    void newConnection(size_t player);
    void recived(size_t player, std::unique_ptr<BinaryPackage>);

    std::unique_ptr<Serialization> _data;
    size_t                         _tick;

    std::unique_ptr<Iyathuum::UpdateTimer> _timer     ;
    std::unique_ptr<NetworkMemoryWriter>   _writer    ;
    std::unique_ptr<Connection>            _connection;
    std::vector<std::unique_ptr<ICommand>> _onUpdate  ;
    
  };
}