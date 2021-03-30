#pragma once

#include <memory>
#include <functional>

#include "VishalaNetworkLib/Core/Command.h"
#include "IyathuumCoreLib/Util/UpdateTimer.h"
#include "IyathuumCoreLib/Util/Scheduler.h"
#include "VishalaNetworkLib/Core/Connection.h"

namespace Vishala {
  template<typename T>
  class LiberalGameClient {
    LiberalGameClient(std::shared_ptr<T>& data, int ticksPerSecond, int port, int serverPort, std::string serverIP) {

    }

    void update() {

    }

    void sendCmd(const ICommand& cmd) {
      std::unique_ptr<BinaryPackage> toSend = std::make_unique<BinaryPackage>(cmd.serialize());
      _connection->send(0, 0, std::move(toSend));
    }

  private:
    std::shared_ptr<T>& _data      ;
    size_t              _tick = 0  ; 

    int                 _port      ;
    int                 _serverPort;
    std::string         _ip        ;

    std::unique_ptr<Iyathuum::UpdateTimer> _timer     ;
    std::unique_ptr<Iyathuum::Scheduler  > _scheduler ;
    std::unique_ptr<Connection>            _connection;

  };
}