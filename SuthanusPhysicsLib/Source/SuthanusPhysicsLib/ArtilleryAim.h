#pragma once

#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>

namespace Suthanus
{
  class ArtilleryAim
  {
  public:
    static glm::vec3 aimSpring(const glm::vec3& targetPositionDifference, float projectileSpeed,bool high = false,float gravity = -9.81f);
  };
}