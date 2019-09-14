#pragma once

#include "Lib/nop/structure.h"
#include "Vector3.h"

namespace Serial {
  struct Vector3 {
    float X;
    float Y;
    float Z;
    NOP_STRUCTURE(Vector3, X, Y, Z);
  };
}