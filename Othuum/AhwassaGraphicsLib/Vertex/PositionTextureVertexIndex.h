#pragma once

#include "IVertex.h"
#include "IyathuumCoreLib/lib/glm/glm.hpp"
#include <vector>

namespace Ahwassa {
  struct AttributeDescription;

  struct PositionTextureVertexIndex {
    glm::vec3 position;
    glm::vec2 texture ;
    float     index   ;

    PositionTextureVertexIndex();
    PositionTextureVertexIndex(glm::vec3 Position, glm::vec2 Texture, float index);

    static std::vector<AttributeDescription> getBinding();
    std::vector<AttributeDescription> binding();
  };
}