#pragma once

#include "BufferObjects/Mesh.h"
#include "Vertex/PositionNormalVertex.h"

namespace Ahwassa {

  class Util {
  public:
    static double getTime();
    static size_t maxUniformAmount();
    static void setDepthTest(bool enabled);
    static void setDepthFuncLess();

    static std::shared_ptr<Mesh<PositionNormalVertex>> getCube();
  };
}