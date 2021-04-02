#pragma once

#include "IyathuumCoreLib/lib/glm/glm.hpp"
#include <vector>

namespace Ahwassa {
  struct AttributeDescription;

  struct PositionTextureVertex {
    glm::vec3 position;
    glm::vec2 texture ;

    PositionTextureVertex();
    PositionTextureVertex(glm::vec3 Position, glm::vec2 Texture);

    static std::vector<AttributeDescription> getBinding();
  };
}