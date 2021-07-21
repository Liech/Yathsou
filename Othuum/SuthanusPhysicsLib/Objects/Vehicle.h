#pragma once

#include "PhysicObject.h"

namespace Suthanus
{
  class Vehicle : public PhysicObject
  {
  public:
    virtual glm::vec3 getSize()              = 0;
                                             
    virtual float     maxSteering()          = 0;
    virtual void      setSteering(float)     = 0;

    virtual float     maxAcceleration()      = 0;
    virtual void      setAcceleration(float) = 0;
  };
}