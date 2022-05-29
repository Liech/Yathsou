#pragma once

#include "AhwassaGraphicsLib/Renderer/RendererTemplate.h"
#include "AhwassaGraphicsLib/Renderer/ColorAndTransformation.h"




namespace Ahwassa {
  class DiffuseDirectMeshRenderer : public RendererTemplate<ColorAndTransformation> {
    public:

    protected:
     virtual std::string vertexShader()                                                   override;
     virtual std::string fragmentShader()                                                 override;
     virtual std::vector<std::shared_ptr<Ahwassa::Uniform>> initUniforms()                override;
     virtual void vectorize(const size_t& index, std::shared_ptr<ColorAndTransformation>) override;
     virtual void bind()                                                                  override;


    private:

  };
}