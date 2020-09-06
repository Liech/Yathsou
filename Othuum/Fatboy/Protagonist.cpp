#include "Protagonist.h"

#include "YolonaOss/Renderer/BoxRenderer.h"
#include "YolonaOss/OpenGL/Window.h"

namespace Fatboy
{
  Protagonist::Protagonist()
  {
  }

  void Protagonist::load(YolonaOss::GL::DrawSpecification* spec)
  {
    _spec = spec;
  }

  void Protagonist::draw()
  {
    YolonaOss::BoxRenderer::start();
    YolonaOss::BoxRenderer::drawDot(getPosition(), glm::vec3(1, 1, 1), glm::vec4(1,0,0,1));
    YolonaOss::BoxRenderer::end();
  }

  void Protagonist::update()
  {
    handleInput();
  }

  void Protagonist::handleInput()
  {
    auto isPressed = [this](YolonaOss::GL::Key key) {
      return _spec->getWindow()->getKeyStatus(key) == YolonaOss::GL::KeyStatus::PRESS;
    };
    if (isPressed(YolonaOss::GL::Key::KEY_W))
    {
      _pos = _pos - glm::vec3(0.1, 0, 0);
    }
    else if (isPressed(YolonaOss::GL::Key::KEY_S))
    {
      _pos = _pos + glm::vec3(0.1, 0, 0);
    }
    if (isPressed(YolonaOss::GL::Key::KEY_A))
    {
      _pos = _pos + glm::vec3(0, 0, 0.1);
    }
    else if (isPressed(YolonaOss::GL::Key::KEY_D))
    {
      _pos = _pos - glm::vec3(0, 0, 0.1);
    }
  }

  glm::vec3 Protagonist::getPosition()
  {
    return _pos;
  }

}