#pragma once

#include <string>
#include <array>
#include <vector>

#include "LobbyGame.h"

namespace Vishala {
  class LobbyStateUpdate {
  public:
    std::vector<LobbyGame> openGames;
  };
}