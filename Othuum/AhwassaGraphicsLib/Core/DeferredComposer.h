#pragma once

#include <memory>
#include <vector>
#include "AhwassaGraphicsLib/Vertex/PositionTextureVertex.h"
#include "AhwassaGraphicsLib/BasicRenderer/BasicTexture2DRenderer.h"
#include "AhwassaGraphicsLib/BufferObjects/VBO.h"

namespace Ahwassa {
  class FBO;
  class Texture;
  class ShaderProgram;
  class Window;
  class Texture;
  class Rendertarget;
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
    BasicTexture2DRenderer r;

    std::unique_ptr<VBO<PositionTextureVertex>>              _vbo;
    std::unique_ptr<VAO>               _vao;
    std::vector<PositionTextureVertex> _vertices;
    std::shared_ptr<ShaderProgram>     _shader;
    std::unique_ptr<UniformMat4>       _projection;
    int _width;
    int _height;
  };
}