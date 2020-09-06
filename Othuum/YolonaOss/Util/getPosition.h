#pragma once

#include "IyathuumCoreLib/lib/glm/vec3.hpp"
namespace YolonaOss
{
  class GetPosition
  {
  public:
    virtual glm::vec3 getPosition() = 0;
  };
}