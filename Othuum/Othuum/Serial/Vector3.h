#pragma once

#include "../Lib/nop/structure.h"

namespace Serial {
  struct Vector3 {
    float X;
    float Y;
    float Z;
    NOP_STRUCTURE(Vector3, X, Y, Z);
  };
}