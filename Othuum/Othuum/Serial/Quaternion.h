#pragma once

#include "../Lib/nop/structure.h"
#include "Vector3.h"

namespace Serial {
  struct Quaternion {
    float W;
    float X;
    float Y;
    float Z;
    NOP_STRUCTURE(Quaternion, X, Y, Z, W);
  };
}