#pragma once

#include "Lib/nop/structure.h"
#include "Vector3.h"

namespace Serial {
  struct MovementCommand {
    Vector3 position;
    NOP_STRUCTURE(MovementCommand, position);
  };
}