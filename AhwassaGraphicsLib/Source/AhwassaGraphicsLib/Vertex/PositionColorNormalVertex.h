#pragma once

#include "IVertex.h"
#include <glm/glm.hpp>
#include <vector>

namespace Ahwassa {
  struct AttributeDescription;

  struct PositionColorNormalVertex {//: public IVertex {
    glm::vec3 position;
    glm::vec4 color   ;
    glm::vec3 normal  ;

    PositionColorNormalVertex();
    PositionColorNormalVertex(glm::vec3 Position, glm::vec4 Color, glm::vec3 Normal);

    static std::vector<AttributeDescription> getBinding();
    std::vector<AttributeDescription> binding();
  };
}