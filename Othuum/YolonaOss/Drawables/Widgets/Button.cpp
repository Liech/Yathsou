#include "Button.h"

#include "glad/glad.h"
#include "../../Renderer/RectangleRenderer.h"
#include "../../Renderer/TextRenderer.h"

namespace YolonaOss {
  Button::Button() : Widget()
  {
    _name = "Def";
  }


  Button::~Button()
  {
  }

  void Button::load(GL::DrawSpecification*)
  {

  }

  void Button::draw()
  {
    RectangleRenderer::startTextRender();
    RectangleRenderer::drawRectangle(getPosition(), _hovered ? glm::vec3(0.8f, 0.8f, 0.8f) : glm::vec3(0.4f, 0.4f, 0.4f));
    RectangleRenderer::endTextRender();
    glm::vec2 textSize = TextRenderer::getTextSize(_name, 1);
    glm::vec2 spacing = (getPosition().size - textSize) / 2.0f;
    TextRenderer::startTextRender();
    glm::vec2 pos = getPosition().position + spacing;
    TextRenderer::drawText(_name, pos, 1, glm::vec3(0, 0, 0));
    TextRenderer::endTextRender();
  }

  void Button::mouseEnter() {
    _hovered = true;
  };

  void Button::mouseLeave() {
    _hovered = false;
  };

  void Button::mouseClick(glm::vec2 position, GL::Key k) {
    _clickedFunction();
  };
}