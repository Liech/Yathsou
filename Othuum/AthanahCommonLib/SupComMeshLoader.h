#pragma once

#include "AezeselFileIOLib/SCM.h"
#include "AhwassaGraphicsLib/BufferObjects/Mesh.h"
#include "AhwassaGraphicsLib/Vertex/PositionNormalVertex.h"

namespace Athanah {
  class SupComModel;

  class SupComMeshLoader {
  public:
    static std::shared_ptr<Ahwassa::Mesh<Ahwassa::PositionNormalVertex>> loadBasic(std::string filename);
  };
}