#pragma once

#include "Lib/nop/structure.h"
#include "Vector3.h"

namespace Serial {
  struct Unit {
    Vector3 position;
    NOP_STRUCTURE(Unit, position);
  };
}