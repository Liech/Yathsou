#pragma once

#include "IyathuumCoreLib/lib/glm/glm.hpp"

namespace Suthanus
{
  class PhysicObject
  {
  public:
    virtual glm::vec3 getPosition()       = 0;
    virtual glm::mat4 getTransformation() = 0;
  };
}