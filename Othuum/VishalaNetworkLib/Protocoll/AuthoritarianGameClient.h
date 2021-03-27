#pragma once

#include <memory>
#include <functional>
#include "VishalaNetworkLib/Core/Serialization.h"

namespace Iyathuum {
  class UpdateTimer;
  class Scheduler;
}

namespace Vishala {
  class ICommand;  
  class Connection;
  class BinaryPackage;
  class NetworkMemoryReader;

  class AuthoritarianGameClient {
  public:
    AuthoritarianGameClient(std::shared_ptr<Serialization>& data,int ticksPerSecond, int port, int serverPort, std::string serverIP);
    void update();
    void sendCmd(const ICommand& cmd);

  private:
    void nextTick();
    void initConnection();

  private:
    std::shared_ptr<Serialization>& _data;
    int            _port;
    int            _serverPort;
    std::string    _ip  ;

    std::unique_ptr<Iyathuum::UpdateTimer> _timer     ;
    std::unique_ptr<NetworkMemoryReader>   _reader    ;
    std::unique_ptr<Connection>            _connection;
  };
}