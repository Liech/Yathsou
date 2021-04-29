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

  class AdditiveComposer : public PostProcessingEffect {
  public:
    AdditiveComposer(Ahwassa::Window* w, std::vector<std::shared_ptr<Ahwassa::Texture>> textures, int width, int height);
    void draw();

  private:
    std::shared_ptr<Ahwassa::ShaderProgram> _shader;

    std::vector<std::shared_ptr<Ahwassa::Texture>> _textures;
  };
}