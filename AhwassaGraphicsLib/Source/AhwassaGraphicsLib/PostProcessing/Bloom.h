#pragma once

#include "PostProcessingEffect.h"

namespace Ahwassa {
  class Texture;
  class ShaderProgram;
  class Window;
  class Texture;
  class Rendertarget;
  class VAO;
  class UniformMat4;
  class UniformFloat;
  class Window;

  class Bloom : public PostProcessingEffect {
  public:
    Bloom(Ahwassa::Window* w, const glm::ivec2&);
    void draw(std::shared_ptr<Ahwassa::Texture> input, std::shared_ptr<Ahwassa::Texture> bloom, int channel);

    void setIntensity(float);
    float intensity();
    void  setSize(float);
    float size();
    void  setQuality(float);
    float quality();
    void  setDirections(float);
    float directions();
  private:
    std::shared_ptr<Ahwassa::ShaderProgram> _shader;

    std::shared_ptr<Ahwassa::Texture>       _bloomMap    ;
    std::shared_ptr<Ahwassa::Texture>       _input       ;
    std::shared_ptr<Ahwassa::UniformFloat>  _bloomChannel;
    std::shared_ptr<Ahwassa::UniformFloat>  _intensity   ;
    std::shared_ptr<Ahwassa::UniformFloat>  _size        ;
    std::shared_ptr<Ahwassa::UniformFloat>  _quality     ;
    std::shared_ptr<Ahwassa::UniformFloat>  _directions  ;

    bool _enabled = true;
  };
}