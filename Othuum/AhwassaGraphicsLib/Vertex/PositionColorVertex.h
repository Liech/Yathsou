#pragma once

#include "IyathuumCoreLib/lib/glm/glm.hpp"
#include <vector>

namespace Ahwassa {
  struct AttributeDescription;

  struct PositionColorVertex {
    glm::vec3 position;
    glm::vec4 color;

    PositionColorVertex();
    PositionColorVertex(glm::vec3 Position, glm::vec4 Color);

    static std::vector<AttributeDescription> getBinding();
  };
}