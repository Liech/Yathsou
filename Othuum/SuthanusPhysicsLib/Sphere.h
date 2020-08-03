#pragma once

#include "PhysicObject.h"

class btRigidBody;
namespace Suthanus
{
  class Sphere : public PhysicObject
  {
  public:
    virtual float getRadius() = 0;
  };
}