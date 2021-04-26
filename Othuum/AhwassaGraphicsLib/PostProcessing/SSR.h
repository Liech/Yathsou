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

  class SSR : public PostProcessingEffect {
  public:
    SSR(Ahwassa::Window* w, int width, int height);
    void draw(std::shared_ptr<Ahwassa::Texture> input, std::shared_ptr<Ahwassa::Texture> reflections, int channel);
  private:
    std::shared_ptr<Ahwassa::ShaderProgram> _shader;

    std::shared_ptr<Ahwassa::Texture>       _reflectionMap;
    std::shared_ptr<Ahwassa::Texture>       _input;

    bool _enabled = true;
  };
}