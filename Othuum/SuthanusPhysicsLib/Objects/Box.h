#pragma once

#include "PhysicObject.h"

class btRigidBody;
namespace Suthanus
{
  class Box : public PhysicObject
  {
  public:
    virtual glm::vec3 getSize() = 0;
  };
}