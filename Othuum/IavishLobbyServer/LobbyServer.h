#pragma once


#include "VishalaNetworkLib/Lobby.h"

namespace Iavish {
  class LobbyServer {
  public:
    void run();

  private:
    std::unique_ptr<Vishala::Lobby> _lobby;
  };
}