#pragma once

#include "IVertex.h"
#include "IyathuumCoreLib/lib/glm/glm.hpp"
#include <vector>

namespace Ahwassa {
  struct AttributeDescription;

  struct PositionColorVertex {//: public IVertex {
    glm::vec3 position;
    glm::vec4 color;

    PositionColorVertex();
    PositionColorVertex(glm::vec3 Position, glm::vec4 Color);

    static std::vector<AttributeDescription> getBinding();
    std::vector<AttributeDescription> binding();
  };
}