#pragma once

#include <string>
#include <array>
#include <vector>

#include "LobbyStateUpdate.h"

namespace Vishala {
  class LobbyBriefing {
  public:
    size_t            playerId   ;
    LobbyStateUpdate  lobbyStatus;
  };
}