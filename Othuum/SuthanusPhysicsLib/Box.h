#pragma once

#include "IyathuumCoreLib/lib/glm/vec3.hpp"

class btRigidBody;
namespace Suthanus
{
  class Box
  {
  public:
    virtual glm::vec3 getPosition() = 0;
  };
}