#pragma once

#include "Vector3.h"
#include "Quaternion.h"

//this is for mass extraction points
namespace Serial {
  struct Entity {
    Vector3    position;
    Quaternion orientation;
    size_t     modelID;
  };
}