#pragma once

#include "Vector3.h"
#include "Quaternion.h"
#include "Entity.h"
//this is for mass extraction points
namespace Serial {
  struct MoveableEntity : Entity{
    Vector3 velocity;
  };
}