#pragma once

#include "PhysicObject.h"

namespace Suthanus
{
  class Vehicle : public PhysicObject
  {
  public:
    virtual glm::vec3 getSize() = 0;
  };
}