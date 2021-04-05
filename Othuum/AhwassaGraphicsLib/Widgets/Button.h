#pragma once

#include <string>
#include <functional>

#include "AhwassaGraphicsLib/Input/UIElement.h"
#include "AhwassaGraphicsLib/Drawables/Drawable.h"

namespace Ahwassa {
  class Button : public UIElement, public Drawable
  {
  public:
    Button(Window* w);
    Button(std::string name, Iyathuum::glmAABB<2> position, std::function<void(void)> clickedFunction, Window* w, std::shared_ptr<UIElement> parent = nullptr);
    ~Button();
    
    virtual void draw() override;

    virtual bool mouseClickEvent(glm::vec2 localPosition, Iyathuum::Key button) override;

    virtual void mouseEnterEvent() override;
    virtual void mouseLeaveEvent() override;

    void setText(std::string t);
  private:
    std::string               _name;
    std::function<void(void)> _clickedFunction;

    bool _hovered = false;
  };
}