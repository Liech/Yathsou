#pragma once

#include <string>

namespace Vishala {
  class GameJoinRequestAnswer {
  public:
    bool        accepted;
    std::string reason  ;
    std::string hostIp  ;
    size_t      playerId;
  };
}