#include "PostProcessingEffect.h"

#include <glm/gtc/matrix_transform.hpp>

#include "AhwassaGraphicsLib/BufferObjects/VAO.h"
#include "AhwassaGraphicsLib/Uniforms/Rendertarget.h"
#include "AhwassaGraphicsLib/Uniforms/Texture.h"
#include "AhwassaGraphicsLib/Uniforms/UniformMat4.h"
#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Core/ShaderProgram.h"
#include "AhwassaGraphicsLib/Core/Renderer.h"
#include "AhwassaGraphicsLib/Util.h"
#include "AhwassaGraphicsLib/BufferObjects/VAO.h"
#include "AhwassaGraphicsLib/Renderer/BasicTexture2DRenderer.h"

namespace Ahwassa {
  PostProcessingEffect::PostProcessingEffect(std::string name, Ahwassa::Window* window, const glm::ivec2& resolution) {
    _result = std::make_shared<Ahwassa::Rendertarget>(name, resolution);
    _resolution = resolution;
    _window = window;
    _name   = name;


    _vertices = {
      Ahwassa::PositionTextureVertex(glm::vec3(0,1, 0),glm::vec2(0.0, 1.0)),
      Ahwassa::PositionTextureVertex(glm::vec3(0,0, 0),glm::vec2(0.0, 0.0)),
      Ahwassa::PositionTextureVertex(glm::vec3(1,0, 0),glm::vec2(1.0, 0.0)),
      Ahwassa::PositionTextureVertex(glm::vec3(0,1, 0),glm::vec2(0.0, 1.0)),
      Ahwassa::PositionTextureVertex(glm::vec3(1,0, 0),glm::vec2(1.0, 0.0)),
      Ahwassa::PositionTextureVertex(glm::vec3(1,1, 0),glm::vec2(1.0, 1.0))
    };

    _projection = std::make_unique<Ahwassa::UniformMat4>("projection");
    _projection->setValue(glm::ortho(0.0f, (float)_resolution[0], 0.0f, (float)_resolution[1]));
    _vbo = std::make_unique<Ahwassa::VBO<Ahwassa::PositionTextureVertex>>(_vertices);
    _vao = std::make_unique<Ahwassa::VAO>(_vbo.get());
  }


  void PostProcessingEffect::start() {
    _result->start();
    Ahwassa::Util::setBlend(true);
    Ahwassa::Util::setDepthTest(false);
    Ahwassa::Util::setTextureBlend();
  }

  void PostProcessingEffect::end() {
    float x = 0;
    float y = 0;
    float w = _resolution[0];
    float h = _resolution[1];
    _vertices = {
      Ahwassa::PositionTextureVertex(glm::vec3(x + 0, y + h, 0),glm::vec2(0.0, 1.0)),
      Ahwassa::PositionTextureVertex(glm::vec3(x + 0, y + 0, 0),glm::vec2(0.0, 0.0)),
      Ahwassa::PositionTextureVertex(glm::vec3(x + w, y + 0, 0),glm::vec2(1.0, 0.0)),
      Ahwassa::PositionTextureVertex(glm::vec3(x + 0, y + h, 0),glm::vec2(0.0, 1.0)),
      Ahwassa::PositionTextureVertex(glm::vec3(x + w, y + 0, 0),glm::vec2(1.0, 0.0)),
      Ahwassa::PositionTextureVertex(glm::vec3(x + w, y + h, 0),glm::vec2(1.0, 1.0))
    };

    _vbo->setData(_vertices);
    _vao->draw();

    _result->end();
  }

  std::shared_ptr<Ahwassa::Texture> PostProcessingEffect::getResult() {
    std::shared_ptr<Ahwassa::Texture> result = std::make_shared<Ahwassa::Texture>(_name, _result->getTextureID());
    result->release();
    return result;
  }

  void PostProcessingEffect::drawResult() {
    _window->renderer().texture().start();
    _window->renderer().texture().draw(*getResult(), Iyathuum::glmAABB<2>(glm::vec2(0, 0), glm::vec2(_resolution[0], _resolution[1])), true);
    _window->renderer().texture().end();
  }

  int PostProcessingEffect::getWidth() {
    return _resolution[0];
  }

  int PostProcessingEffect::getHeight() {
    return _resolution[1];
  }

  Ahwassa::Window* PostProcessingEffect::getWindow() {
    return _window;
  }

  std::vector<Ahwassa::Uniform*> PostProcessingEffect::getUniforms() {
    std::vector<Ahwassa::Uniform*> result;
    result.push_back(_projection.get());
    return result;
  }


  bool  PostProcessingEffect::enabled() {
    return _enabled;
  }

  void  PostProcessingEffect::setEnabled(bool value) {
    _enabled = value;
  }
}