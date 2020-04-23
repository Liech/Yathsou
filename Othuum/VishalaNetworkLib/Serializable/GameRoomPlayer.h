#pragma once

#include <string>
#include <array>

namespace Vishala {
  class GameRoomPlayer {
  public:
    std::string        name;
    size_t             id  ;
    std::array<int, 3> color;
  };
}