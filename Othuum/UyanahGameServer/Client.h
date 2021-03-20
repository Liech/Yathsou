#pragma once

#include <memory>
namespace Vishala { class Connection; }
namespace Vishala { class ConnectionMultiplexer; }

#include "VishalaNetworkLib/Core/NetworkMemory.h"

namespace Uyanah {
  class Scene;
  class ClientConfiguration;

  class Client
  {
  public:
    Client();
    ~Client();

    void setConfig(ClientConfiguration conifg);
    void start();
    void stop();
    void update();

    const Scene& getScene();

  private:

    std::unique_ptr<Vishala::NetworkMemoryReader<Scene>>  _scene = nullptr;
    std::shared_ptr<Vishala::Connection>                  _connection;
    std::shared_ptr<Vishala::ConnectionMultiplexer>       _multiplexer;
    std::unique_ptr<ClientConfiguration>                  _config;
    bool                                                  _stop = false;
  };
}