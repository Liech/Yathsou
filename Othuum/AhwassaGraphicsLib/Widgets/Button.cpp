#include "Button.h"

#include "IyathuumCoreLib/Singleton/Database.h"
#include "BasicRenderer/BasicRectangleRenderer.h"
#include "BasicRenderer/BasicTextRenderer.h"
#include "Core/Window.h"
#include "Core/Renderer.h"

namespace Ahwassa {
  Button::Button(Window* w) : Drawable(w)
  {
    _name = "Def";
  }

  Button::Button(std::string name, Iyathuum::glmAABB<2> position, std::function<void(void)> clickedFunction, Window* w, UIElement* parent) : Drawable(w)
  {
    _clickedFunction = clickedFunction;
    _name = name;
    setLocalPosition(position);
    setParent(parent);
  }

  Button::~Button()
  {
    setVisible(false);
  }

  void Button::draw()
  {
    if (!isVisible())
      return;

    getWindow()->renderer().rectangle().start();
    getWindow()->renderer().rectangle().drawRectangle(getGlobalPosition(), _hovered ? Iyathuum::Color(0.8f*255, 0.8f * 255, 0.8f * 255) : Iyathuum::Color(0.4f * 255, 0.4f * 255, 0.4f * 255));
    getWindow()->renderer().rectangle().end();
    glm::vec2 textSize = getWindow()->renderer().text().getTextSize(_name, 1);
    glm::vec2 spacing = (glm::vec2(getGlobalPosition().getSize()[0], getGlobalPosition().getSize()[1]) - textSize) / 2.0f;
    getWindow()->renderer().text().start();
    glm::vec2 pos = getGlobalPosition().getPosition() + spacing;
    getWindow()->renderer().text().drawText(_name, pos, 1, Iyathuum::Color(0, 0, 0));
    getWindow()->renderer().text().end();
  }

  void Button::setText(std::string t)
  {
    _name = t;
  }

  bool Button::mouseClickEvent(glm::vec2 localPosition, Iyathuum::Key button) {
    _clickedFunction();
    return true;
  }

  void Button::mouseEnterEvent() {
    _hovered = true;
  };

  void Button::mouseLeaveEvent() {
    _hovered = false;
  };
}
