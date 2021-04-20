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
    Bloom(Ahwassa::Window* w, int width, int height);
    void draw(std::shared_ptr<Ahwassa::Texture> input, std::shared_ptr<Ahwassa::Texture> bloom, int channel);
  private:  
    std::shared_ptr<Ahwassa::ShaderProgram>                       _shader;

    std::shared_ptr<Ahwassa::Texture>                             _bloomMap;
    std::shared_ptr<Ahwassa::Texture>                             _input;
    std::shared_ptr<Ahwassa::UniformFloat>                        _bloomChannel;
  };
}