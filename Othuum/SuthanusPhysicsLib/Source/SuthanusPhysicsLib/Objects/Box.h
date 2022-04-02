#pragma once

#include "PhysicObject.h"

class btRigidBody;
namespace Suthanus
{
  class PhysicEngine;

  class Box : public PhysicObject
  {
  public:
    Box(PhysicEngine&);
    virtual ~Box() = default;

    virtual glm::vec3 getSize() = 0;
  };
}