#pragma once


#include "VishalaNetworkLib/Protocoll/Server/Lobby.h"

namespace Iavish {
  class LobbyServer {
  public:
    void run();

  private:
    std::unique_ptr<Vishala::Server::Lobby> _lobby;
  };
}