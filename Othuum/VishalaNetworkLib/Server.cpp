#include "Server.h"

#include "enet/enet.h"

namespace Vishala {
  class Server::pimpl {
  public:
    ENetHost* _server     ;
    int       _port = 6112;
  };

  Server::Server() {
    p = new Server::pimpl();
  }

  Server::~Server() {
    delete p;
  }

}