#pragma once

#include "PostProcessingEffect.h"

namespace Ahwassa {
  class Texture;
  class ShaderProgram;
  class Window;
  class Rendertarget;
  class VAO;
  class UniformMat4;
  class UniformFloat;
  class UniformVec3;
  class Window;
  class CubeTexture;

  class CubeReflection : public PostProcessingEffect {
  public:
    CubeReflection(Ahwassa::Window* w, int width, int height);
    void draw(glm::vec3 viewPos, std::shared_ptr<Ahwassa::Texture> input, std::shared_ptr<Ahwassa::Texture> reflections, std::shared_ptr<Ahwassa::Texture> gPosition, std::shared_ptr<Ahwassa::Texture> normal, int channel);
    void setTexture(std::shared_ptr<Ahwassa::CubeTexture>);
  private:
    std::shared_ptr<Ahwassa::ShaderProgram> _shader;

    std::shared_ptr<Ahwassa::UniformFloat>  _reflectionChannel;
    std::shared_ptr<Ahwassa::UniformVec3>   _viewPosition;
    std::shared_ptr<Ahwassa::Texture>       _reflectionIntensityMap;
    std::shared_ptr<Ahwassa::Texture>       _gPosition;
    std::shared_ptr<Ahwassa::Texture>       _normalMap;
    std::shared_ptr<Ahwassa::CubeTexture>   _reflectionTexture;
    std::shared_ptr<Ahwassa::Texture>       _input;

    bool _enabled = true;
  };
}