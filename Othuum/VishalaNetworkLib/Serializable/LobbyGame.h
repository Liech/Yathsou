#pragma once

#include <string>
#include <vector>
#include "GameRoomPlayer.h"

namespace Vishala {
  class LobbyGame {
  public:
    std::string name              ;
    size_t      numberOfPlayers   ;
    size_t      maxNumberOfPlayers;
  };
}