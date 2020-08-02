#pragma once

#include "IyathuumCoreLib/lib/glm/glm.hpp"

class btRigidBody;
namespace Suthanus
{
  class Box
  {
  public:
    virtual glm::vec3 getSize()           = 0;
    virtual glm::vec3 getPosition()       = 0;
    virtual glm::mat4 getTransformation() = 0;
  };
}