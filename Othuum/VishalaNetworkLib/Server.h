#pragma once

#include <memory>

namespace Vishala {
  class Server {
  public:
    Server();
    virtual ~Server();

  private:
    class pimpl;
    Server::pimpl* p;
  };
}