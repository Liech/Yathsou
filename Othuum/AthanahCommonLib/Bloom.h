#pragma once

#include <memory>
#include "AhwassaGraphicsLib/BufferObjects/VBO.h"
#include "AhwassaGraphicsLib/Vertex/PositionTextureVertex.h"

namespace Ahwassa {
  class FBO;
  class Texture;
  class ShaderProgram;
  class Window;
  class Texture;
  class Rendertarget;
  class VAO;
  class UniformMat4;
  class UniformFloat;
  class Window;
}

namespace Athanah {
  class Bloom {
  public:
    Bloom(Ahwassa::Window* w, int width, int height);
    void draw(std::shared_ptr<Ahwassa::Texture> input, std::shared_ptr<Ahwassa::Texture> bloom, int channel);
    std::shared_ptr<Ahwassa::Texture> getResult();
    void drawResult();
  private:  
    std::unique_ptr<Ahwassa::VBO<Ahwassa::PositionTextureVertex>> _vbo;
    std::unique_ptr<Ahwassa::VAO>                                 _vao;
    std::shared_ptr<Ahwassa::Rendertarget>                        _result;
    std::shared_ptr<Ahwassa::ShaderProgram>                       _shader;
    std::unique_ptr<Ahwassa::UniformMat4>                         _projection;
    std::vector<Ahwassa::PositionTextureVertex>                   _vertices;

    std::shared_ptr<Ahwassa::Texture>                             _bloomMap;
    std::shared_ptr<Ahwassa::Texture>                             _input;
    std::shared_ptr<Ahwassa::UniformFloat>                        _bloomChannel;

    int                                                           _width;
    int                                                           _height;
    Ahwassa::Window*                                              _window;
  };
}