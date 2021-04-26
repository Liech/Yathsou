#include "Checkbox.h"

#include "IyathuumCoreLib/Singleton/Database.h"
#include "BasicRenderer/BasicRectangleRenderer.h"
#include "BasicRenderer/BasicTextRenderer.h"
#include "Core/Window.h"
#include "Core/Renderer.h"
#include "Input/Input.h"

namespace Ahwassa {
  Checkbox::Checkbox(Window* w) : Drawable(w)
  {
    _name = "Def";
  }

  Checkbox::Checkbox(std::string name,bool value, Iyathuum::glmAABB<2> position, std::function<void(bool)> clickedFunction, Window* w, UIElement* parent) : Drawable(w)
  {
    _checked = value;
    _clickedFunction = clickedFunction;
    _name = name;
    w->input().addUIElement(this);
    setLocalPosition(position);
    setParent(parent);
  }

  Checkbox::~Checkbox()
  {
    getWindow()->input().removeUIElement(this);
    setVisible(false);
  }

  void Checkbox::draw()
  {
    if (!isVisible())
      return;
    auto glob = getGlobalPosition();
    getWindow()->renderer().rectangle().start();
    getWindow()->renderer().rectangle().drawRectangle(glob, _hovered ? Iyathuum::Color(0.8f*255, 0.8f * 255, 0.8f * 255) : Iyathuum::Color(0.4f * 255, 0.4f * 255, 0.4f * 255));
    getWindow()->renderer().rectangle().end();
    glm::vec2 textSize = getWindow()->renderer().text().getTextSize(_name, _textSize);
    glm::vec2 spacing = (glm::vec2(getGlobalPosition().getSize()[0], getGlobalPosition().getSize()[1]) - textSize) / 2.0f;
    getWindow()->renderer().text().start();
    glm::vec2 pos = getGlobalPosition().getPosition() + spacing;
    getWindow()->renderer().text().drawText((_checked?"[x]":"[ ]") +  _name, pos, _textSize, Iyathuum::Color(0, 0, 0));
    getWindow()->renderer().text().end();
  }

  void Checkbox::setText(std::string t)
  {
    _name = t;
  }

  bool Checkbox::mouseClickEvent(glm::vec2 localPosition, Iyathuum::Key Checkbox) {
    _checked = !_checked;
    _clickedFunction(_checked);
    return true;
  }

  void Checkbox::mouseEnterEvent() {
    _hovered = true;
  };

  void Checkbox::mouseLeaveEvent() {
    _hovered = false;
  };

  void Checkbox::setTextSize(float size) {
    _textSize = size;
  }

  void Checkbox::setChecked(bool value) {
    _checked = true;
  }

  bool Checkbox::isChecked() {
    return _checked;
  }

}
