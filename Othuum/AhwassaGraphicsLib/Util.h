#pragma once

#include "BufferObjects/Mesh.h"
#include "Vertex/PositionNormalVertex.h"
#include <utility>

namespace Ahwassa {

  class Util {
  public:
    static double getTime();
    static size_t maxUniformAmount();
    static void setDepthTest(bool enabled);
    static void setBlend(bool enabled);
    static void setDepthFuncLess();
    static void setDepthFuncMore();
    static void setCulling(bool front);
    static void enableCulling(bool enabled);
    static void depthMask(bool enabled);
    static void setWireframe(bool enabled);
    static void setTextureBlend();

    static std::shared_ptr<Mesh<PositionNormalVertex>> getCubeMesh();
    static std::pair<std::vector<PositionNormalVertex>, std::vector<int>> getCube();
  };
}