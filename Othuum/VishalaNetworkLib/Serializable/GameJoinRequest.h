#pragma once

#include <string>

namespace Vishala {
  class GameJoinRequest {
  public:
    std::string password  ;
    std::string playerName;
    size_t      gameId    ;
  };
}