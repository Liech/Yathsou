#include "Label.h"

#include "IyathuumCoreLib/Singleton/Database.h"
#include "BasicRenderer/BasicRectangleRenderer.h"
#include "BasicRenderer/BasicTextRenderer.h"
#include "Core/Window.h"
#include "Core/Renderer.h"

namespace Ahwassa {
  Label::Label(Window* w) : Drawable(w)
  {
    _name = "Def";
  }

  Label::Label(std::string name, Iyathuum::glmAABB<2> position, Window* w, UIElement* parent) : Drawable(w) {
    _name = name;
    setParent(parent);
    setLocalPosition(position);
  }

  Label::~Label()
  {
  }

  void Label::draw()
  {
    if (!isVisible())
      return;

    getWindow()->renderer().rectangle().start();
    getWindow()->renderer().rectangle().drawRectangle(getGlobalPosition(), Iyathuum::Color(0.6f*255, 0.6f * 255, 0.6f * 255));
    getWindow()->renderer().rectangle().end();
    glm::vec2 textSize = getWindow()->renderer().text().getTextSize(_name, 1);
    glm::vec2 spacing = (glm::vec2(getGlobalPosition().getSize()[0], getGlobalPosition().getSize()[1]) - textSize) / 2.0f;
    getWindow()->renderer().text().start();
    glm::vec2 pos = getGlobalPosition().getPosition() + spacing;
    getWindow()->renderer().text().drawText(_name, pos, 1, Iyathuum::Color(0, 0, 0));
    getWindow()->renderer().text().end();
  }
}