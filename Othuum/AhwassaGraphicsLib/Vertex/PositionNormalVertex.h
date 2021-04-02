#pragma once

#include "IyathuumCoreLib/lib/glm/glm.hpp"
#include <vector>

namespace Ahwassa {
  struct AttributeDescription;

  struct PositionNormalVertex {
    glm::vec3 position;
    glm::vec3 normal;

    PositionNormalVertex();
    PositionNormalVertex(glm::vec3 Position, glm::vec3 Normal);

    static std::vector<AttributeDescription> getBinding();
  };
}