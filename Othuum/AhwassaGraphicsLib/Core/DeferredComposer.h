#pragma once

#include <memory>
#include <vector>
#include "AhwassaGraphicsLib/Vertex/PositionTextureVertex.h"

namespace Ahwassa {
  class FBO;
  class Texture;
  class ShaderProgram;
  class Window;
  class Texture;
  class Rendertarget;
  class IVBO;
  class VAO;
  class PositionTextureVertex;
  class UniformMat4;

  class DeferredComposer {
  public:
    DeferredComposer(Window* w, int width, int height);
    void start();
    void end();
    std::vector<std::shared_ptr<Texture>> getRawTextures();
    std::shared_ptr<Texture> getResult();
  private:
    std::shared_ptr<Rendertarget>           _resultCanvas;
    std::shared_ptr<FBO>                    _fbo;


    std::unique_ptr<IVBO>              _vbo;
    std::unique_ptr<VAO>               _vao;
    std::vector<PositionTextureVertex> _vertices;
    std::shared_ptr<ShaderProgram>     _shader;
    std::unique_ptr<UniformMat4>       _projection;
  };
}