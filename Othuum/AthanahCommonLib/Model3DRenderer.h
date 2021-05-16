#pragma once

#include <memory>
#include <map>
#include <vector>
#include "IyathuumCoreLib/lib/glm/glm.hpp"
#include "AhwassaGraphicsLib/Renderer/RendererTemplate.h"

namespace Aezesel {
  class Model3D;
}

namespace Ahwassa {
  class Camera;
  class IMesh;
  class SSBOmat4;
  class Texture;
}

namespace Athanah {
  struct Model3DRendererMesh {
    glm::mat4 transformation;
  };

  class Model3DRenderer : public Ahwassa::RendererTemplate<Model3DRendererMesh> {
  public:
    Model3DRenderer(std::shared_ptr<Ahwassa::Camera> camera);
    virtual ~Model3DRenderer();
    std::shared_ptr<Ahwassa::IMesh> meshFromModel3D(const Aezesel::Model3D&);

  protected:
    virtual std::string vertexShader()   override;
    virtual std::string fragmentShader() override;
    std::vector<std::shared_ptr<Ahwassa::Uniform>> initUniforms();
    void vectorize(const size_t& index, std::shared_ptr<Model3DRendererMesh>) final;
    virtual void bind() final;

  private:
    std::vector<glm::mat4>             _matrices;
    std::vector<glm::mat4>             _rotationMatrices;
    std::shared_ptr<Ahwassa::SSBOmat4> _models   ;
    std::shared_ptr<Ahwassa::SSBOmat4> _modelsRot;
    std::shared_ptr<Ahwassa::Texture > _albedo   ;
  };
}