#include "Button.h"

#include "glad/glad.h"
#include "../../Renderer/RectangleRenderer.h"
#include "../../Renderer/TextRenderer.h"
#include "structs/Database.h"

namespace YolonaOss {
  namespace Widgets {
    Button::Button() : Widget()
    {
      _name = "Def";
    }

    Button::Button(std::string name, BoundingBox2 position, std::function<void(void)> clickedFunction) : Widget(position) {
      _clickedFunction = clickedFunction;
      _name = name;
      Database<Widgets::Widget*>::add(this, { "MouseClick" });
    }


    Button::~Button()
    {
      Database<Widgets::Widget*>::remove(this);
    }

    void Button::load(GL::DrawSpecification*)
    {

    }

    void Button::draw()
    {
      RectangleRenderer::start();
      RectangleRenderer::drawRectangle(getPosition(), _hovered ? glm::vec3(0.8f, 0.8f, 0.8f) : glm::vec3(0.4f, 0.4f, 0.4f));
      RectangleRenderer::end();
      glm::vec2 textSize = TextRenderer::getTextSize(_name, 1);
      glm::vec2 spacing = (getPosition().size - textSize) / 2.0f;
      TextRenderer::start();
      glm::vec2 pos = getPosition().position + spacing;
      TextRenderer::drawText(_name, pos, 1, glm::vec3(0, 0, 0));
      TextRenderer::end();
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
}