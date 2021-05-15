//#pragma once
//
//#include <memory>
//#include <map>
//#include <vector>
//#include "IyathuumCoreLib/lib/glm/glm.hpp"
//#include "AhwassaGraphicsLib/Renderer/RendererTemplate.h"
//
//namespace Ahwassa {
//  class Camera;
//  class IMesh;
//  class SSBOmat4;
//  class Texture;
//}
//
//namespace Athanah {
//  struct Model3DRendererMesh {
//    glm::mat4 transformation;
//  };
//
//  class Model3DRenderer : public Ahwassa::RendererTemplate<Model3DRendererMesh> {
//  public:
//    Model3DRenderer(std::shared_ptr<Ahwassa::Camera> camera);
//    virtual ~Model3DRenderer();
//
//  protected:
//    virtual const std::string vertexShader() const override;
//    virtual const std::string fragmentShader() const override;
//    virtual std::vector<std::shared_ptr<Ahwassa::Uniform>> initUniforms() override;
//    void vectorize(const size_t& index, std::shared_ptr<Model3DRendererMesh>) final;
//    virtual void bind() final;
//
//  private:
//    std::shared_ptr<Ahwassa::SSBOmat4> _models   ;
//    std::shared_ptr<Ahwassa::SSBOmat4> _modelsRot;
//    std::shared_ptr<Ahwassa::Texture > _albedo   ;
//  };
//}