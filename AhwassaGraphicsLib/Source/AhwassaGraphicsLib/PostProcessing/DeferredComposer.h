#pragma once

#include <memory>
#include <vector>
#include <glm/glm.hpp>
#include "AhwassaGraphicsLib/Vertex/PositionTextureVertex.h"
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
  class DirectTexture2DRenderer;

  class DeferredComposer {
  public:
    DeferredComposer(Window* w, const glm::ivec2& resolution);
    void start();
    void end();
    std::vector<std::shared_ptr<Texture>> getRawTextures() const;
    std::shared_ptr<Texture> getResult()                   const;
    std::shared_ptr<Texture> getDepth()                    const;
    void draw();
    void blitDepth();
    void setResolution(const glm::ivec2&);

    float ambient() const;
    void  setAmbient(float value);
    float specular() const;
    void  setSpecular(float value);
    float diffuse() const;
    void  setDiffuse(float value);

  private:
    const int MAXLIGHT = 32;
    std::shared_ptr<Rendertarget>            _resultCanvas;
    std::shared_ptr<FBO>                     _fbo;
    std::shared_ptr<DirectTexture2DRenderer> _textureRenderer;

    std::unique_ptr<VBO<PositionTextureVertex>>              _vbo;
    std::shared_ptr<VAO>               _vao;
    std::vector<PositionTextureVertex> _vertices;
    std::shared_ptr<ShaderProgram>     _shader;
    std::unique_ptr<UniformMat4>       _projection;
    std::shared_ptr<UniformVecVec3>    _lightPositions;
    std::shared_ptr<UniformVecVec3>    _lightColors;
    std::shared_ptr<UniformVec3>       _camPos;
    std::shared_ptr<UniformFloat>      _numberOfLights;
    std::shared_ptr<UniformFloat>      _specular;
    std::shared_ptr<UniformFloat>      _diffuse;
    std::shared_ptr<UniformFloat>      _ambient;
    std::vector<glm::vec3> lights;
    std::vector<glm::vec3> clrs;
    glm::ivec2 _resolution;
    Window*    _window;
  };
}