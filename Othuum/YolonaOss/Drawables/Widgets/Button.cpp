#include "Button.h"

#include "glad/glad.h"
#include "../../Renderer/RectangleRenderer.h"
#include "../../Renderer/TextRenderer.h"
#include "IyathuumCoreLib/Singleton/Database.h"
#include "Util/Util.h"

namespace YolonaOss {
  namespace Widgets {
    Button::Button() : Widget()
    {
      _name = "Def";
      Iyathuum::Database<Widgets::Widget*>::add(this, { "MouseClick" });
    }

    Button::Button(std::string name, Iyathuum::AABB<2> position, std::function<void(void)> clickedFunction) : Widget(position) {
      _clickedFunction = clickedFunction;
      _name = name;
      Iyathuum::Database<Widgets::Widget*>::add(this, { "MouseClick" });
    }


    Button::~Button()
    {
      Iyathuum::Database<Widgets::Widget*>::remove(this);
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
      glm::vec2 spacing = (glm::vec2(getPosition().getSize()[0], getPosition().getSize()[1]) - textSize) / 2.0f;
      TextRenderer::start();
      glm::vec2 pos = Util<2>::array2Vec(getPosition().getPosition()) + spacing;
      TextRenderer::drawText(_name, pos, 1, glm::vec3(0, 0, 0));
      TextRenderer::end();
    }

    void Button::mouseEnter() {
      _hovered = true;
    };

    void Button::mouseLeave() {
      _hovered = false;
    };

    bool Button::mouseClick(glm::vec2 position, GL::Key k) {
      _clickedFunction();
      return true;
    };
  }
}