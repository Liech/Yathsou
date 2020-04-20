#pragma once

#include <string>

#include "VishalaNetworkLib/nop/structure.h"

namespace Vishala {
  struct Message {
    size_t      playerID;
    std::string message ;
    NOP_STRUCTURE(playerID, message);
  };
}