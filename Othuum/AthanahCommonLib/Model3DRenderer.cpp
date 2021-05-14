#include "Model3DRenderer.h"

#include "AhwassaGraphicsLib/Vertex/PositionNormalVertex.h"

namespace Athanah {
  Model3DRenderer::Model3DRenderer(std::shared_ptr<Ahwassa::Camera> camera) : 
    Ahwassa::RendererTemplate<Model3DRendererMesh>(camera,Ahwassa::PositionNormalVertex::getBinding()){
    
  }

  Model3DRenderer::~Model3DRenderer() {

  }

  const std::string Model3DRenderer::vertexShader() const {
    return "";
  }

  const std::string Model3DRenderer::fragmentShader() const {
    return "";
  }

  std::vector<std::shared_ptr<Ahwassa::Uniform>> Model3DRenderer::initUniforms() {
    return {};
  }

  void Model3DRenderer::vectorize(const size_t& index, std::shared_ptr<Model3DRendererMesh>) {

  }

  void Model3DRenderer::bind() {

  }
}