#pragma once

#include "IVertex.h"
#include "IyathuumCoreLib/lib/glm/glm.hpp"
#include <vector>

namespace Ahwassa {
  struct AttributeDescription;

  struct PositionNormalVertex {//: public IVertex {
    glm::vec3 position;
    glm::vec3 normal;

    PositionNormalVertex();
    PositionNormalVertex(glm::vec3 Position, glm::vec3 Normal);

    static std::vector<AttributeDescription> getBinding();
    std::vector<AttributeDescription> binding();
  };
}