#pragma once

#include <string>

#include "VishalaNetworkLib/nop/structure.h"

namespace Vishala {
  struct Message {
    std::string message ;
    size_t      playerID;
    NOP_STRUCTURE(playerID, message);
  };
}