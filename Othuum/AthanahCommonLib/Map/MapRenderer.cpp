#include "MapRenderer.h"

#include "AhwassaGraphicsLib/Vertex/PositionNormalVertex.h"
#include "AhwassaGraphicsLib/Uniforms/UniformVec3.h"
#include "AhwassaGraphicsLib/Uniforms/UniformMat4.h"
#include "AhwassaGraphicsLib/Uniforms/Texture.h"
#include "AhwassaGraphicsLib/Util.h"
#include "AezeselFileIOLib/Model3D.h"
#include "AhwassaGraphicsLib/BufferObjects/Mesh.h"

namespace Athanah {
  MapRenderer::MapRenderer(std::shared_ptr<Ahwassa::Camera> camera){
    _camera = camera;
  }
  
  MapRenderer::~MapRenderer() {
  
  }

  void MapRenderer::draw(std::shared_ptr<Ahwassa::IMesh> mesh) {

  }
}