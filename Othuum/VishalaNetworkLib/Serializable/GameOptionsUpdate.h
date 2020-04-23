#pragma once

#include <string>
#include <vector>

#include "GameRoomPlayer.h"

namespace Vishala {
  class GameOptionUpdate {
  public:
    std::string                 gameName;
    std::vector<GameRoomPlayer> player  ;
  };
}