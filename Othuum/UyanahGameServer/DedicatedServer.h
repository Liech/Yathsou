#pragma once

#include <memory>
#include <future>
#include "VishalaNetworkLib/Core/NetworkMemory.h"
namespace Vishala { class Connection; }


namespace Uyanah {
  class DedicatedServerConfiguration;
  class Scene;

  class DedicatedServer
  {
  public:
    DedicatedServer();
    ~DedicatedServer();

    void setConfig(DedicatedServerConfiguration conifg);
    void start();
    void stop();

  private:
    void newConnection(size_t player);

    void runThread();
    void createTestScene();

    
    std::unique_ptr<Vishala::NetworkMemoryWriter<Scene>> _scene       ;
    std::future<void>                                    _thread      ;
    std::shared_ptr<Vishala::Connection>                 _connection  ;
    std::unique_ptr<DedicatedServerConfiguration>        _config      ;
    bool                                                 _stop = false;
  };
}

