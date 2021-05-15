#pragma once

#include <memory>
#include <vector>
#include "AhwassaGraphicsLib/Vertex/PositionTextureVertex.h"
#include "AhwassaGraphicsLib/BasicRenderer/BasicTexture2DRenderer.h"
#include "AhwassaGraphicsLib/BufferObjects/VBO.h"
#include "AhwassaGraphicsLib/Uniforms/UniformMat4.h"

namespace Ahwassa {
  class FBO;
  class Texture;
  class ShaderProgram;
  class Window; 
  class Texture;
  class Rendertarget;
  class VAO;
  struct PositionTextureVertex;
  class UniformVecVec3;
  class UniformVec3;
  class UniformFloat;
  class Window;

  class DeferredComposer {
  public:
    DeferredComposer(Window* w, int width, int height);
    void start();
    void end();
    std::vector<std::shared_ptr<Texture>> getRawTextures();
    std::shared_ptr<Texture> getResult();
    std::shared_ptr<Texture> getDepth();
    void draw();
  private:
    const int MAXLIGHT = 32;
    std::shared_ptr<Rendertarget>           _resultCanvas;
    std::shared_ptr<FBO>                    _fbo;
    BasicTexture2DRenderer r;

    std::unique_ptr<VBO<PositionTextureVertex>>              _vbo;
    std::unique_ptr<VAO>               _vao;
    std::vector<PositionTextureVertex> _vertices;
    std::shared_ptr<ShaderProgram>     _shader;
    std::unique_ptr<UniformMat4>       _projection;
    std::shared_ptr<UniformVecVec3>    _lightPositions;
    std::shared_ptr<UniformVecVec3>    _lightColors;
    std::shared_ptr<UniformVec3>       _camPos;
    std::shared_ptr<UniformFloat>      _numberOfLights;
    std::vector<glm::vec3> lights;
    std::vector<glm::vec3> clrs;
    int _width;
    int _height;
    Window* _window;
  };
}