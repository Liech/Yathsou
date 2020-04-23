#pragma once

#include <string>
#include <vector>
#include "GameRoomPlayer.h"

namespace Vishala {
  class GameBriefing {
  public:
    std::string                 name  ;
    std::vector<GameRoomPlayer> player;
  };
}