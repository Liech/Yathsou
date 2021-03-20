#pragma once

#include <memory>
#include <future>
namespace Vishala { class Connection; }

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

    std::shared_ptr<Scene> getScene();

  private:
    void runThread();
    void createTestScene();

    std::shared_ptr<Scene>               _scene;
    std::future<void>                    _thread;
    std::unique_ptr<Vishala::Connection> _connection;
    std::unique_ptr<ClientConfiguration> _config;
    bool                                 _stop = false;
  };
}