#pragma once

#include <memory>
#include <functional>
#include "Core/Command.h"

namespace Iyathuum {
  class UpdateTimer;
}

namespace Vishala {  
  struct Serialization;
  class Connection;
  struct BinaryPackage;
  class LiberalMessage;

  //streams exact state to clients. recives and executes cmds from clients. 
  //cpu bound, bad for big synchronization objects, simple, can't desync
  class LiberalGameServer {
  public:
    LiberalGameServer(std::unique_ptr<Serialization> data, int port, int ticksPerSecond);
    void addOnUpdate(std::unique_ptr<ICommand>);
    void update();
    const Serialization& data();

    void setInitializationCommandCreator(std::function<std::shared_ptr<ICommand>()>);

  private:
    void initConnection(int port);
    void nextTick();
    void newConnection(size_t player);
    void recived(size_t player, std::unique_ptr<BinaryPackage>);
    void commandRecived(LiberalMessage&);
    void unpause();

    std::unique_ptr<Serialization> _data;
    size_t                         _tick;
    size_t                         _RTTinTicks = 2;
    bool                           _paused = true;

    std::unique_ptr<Iyathuum::UpdateTimer> _timer     ;
    std::unique_ptr<Connection>            _connection;
    std::vector<std::unique_ptr<ICommand>> _onUpdate  ;
    std::function<std::shared_ptr<ICommand>()> _createInitCmd;

    std::map<size_t, size_t> _reportedTicks;
  };
}