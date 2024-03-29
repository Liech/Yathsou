#pragma once

#include "AhwassaGraphicsLib/BufferObjects/Mesh.h"
#include "AhwassaGraphicsLib/Vertex/PositionNormalVertex.h"

namespace Ahwassa {
  class BasicShapeGenerator {
  public:
    static std::shared_ptr<Mesh<PositionNormalVertex>> getCubeMesh();
    static std::pair<std::vector<PositionNormalVertex>, std::vector<int>> getCube();
  };
}