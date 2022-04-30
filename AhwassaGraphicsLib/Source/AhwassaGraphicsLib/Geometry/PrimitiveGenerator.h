#pragma once

#include <glm/glm.hpp>
#include "AhwassaGraphicsLib/Vertex/PositionNormalVertex.h"

namespace Ahwassa {
  class PrimitiveGenerator {
  public:
    static std::pair<std::vector<PositionNormalVertex>, std::vector<int>> getCube();
    static std::pair<std::vector<PositionNormalVertex>, std::vector<int>> getSphere();
  };
}