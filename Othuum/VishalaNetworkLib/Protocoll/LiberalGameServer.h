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
  class LiberalMessage;

  //streams exact state to clients. recives and executes cmds from clients. 
  //cpu bound, bad for big synchronization objects, simple, can't desync
  class LiberalGameServer {
  public:
    LiberalGameServer(std::unique_ptr<Serialization> data, int port, int ticksPerSecond);
    void addOnUpdate(std::unique_ptr<ICommand>);
    void update();

  private:
    void initConnection(int port);
    void nextTick();
    void newConnection(size_t player);
    void recived(size_t player, std::unique_ptr<BinaryPackage>);
    void commandRecived(const LiberalMessage&);

    std::unique_ptr<Serialization> _data;
    size_t                         _tick;
    size_t                         _RTTinTicks = 1;

    std::unique_ptr<Iyathuum::UpdateTimer> _timer     ;
    std::unique_ptr<Connection>            _connection;
    std::vector<std::unique_ptr<ICommand>> _onUpdate  ;

    std::map<size_t, size_t> _reportedTicks;
  };
}