#pragma once

#include <memory>
#include <future>
namespace Vishala { class Connection; }

namespace Uyanah {
  class ClientConfiguration;

  class Client
  {
  public:
    Client();
    ~Client();

    void setConfig(ClientConfiguration conifg);
    void start();
    void stop();

  private:
    void runThread();

    std::future<void>                    _thread;
    std::unique_ptr<Vishala::Connection> _connection;
    std::unique_ptr<ClientConfiguration> _config;
    bool                                 _stop = false;
  };
}