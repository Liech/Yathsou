#pragma once

#include "PhysicObject.h"

class btRigidBody;
namespace Suthanus
{
  class PhysicEngine;

  class Sphere : public PhysicObject
  {
  public:    
    Sphere(PhysicEngine&);
    ~Sphere() = default;

    virtual float getRadius() const = 0;
  };
}