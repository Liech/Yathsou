#pragma once

#include <string>
#include <functional>

#include "AhwassaGraphicsLib/Input/UIElement.h"
#include "AhwassaGraphicsLib/Drawables/Drawable.h"

namespace Ahwassa {
  class Checkbox : public UIElement, public Drawable
  {
  public:
    Checkbox(Window* w);
    Checkbox(std::string name, Iyathuum::glmAABB<2> position, std::function<void(bool)> clickedFunction, Window* w, UIElement* parent = nullptr);
    ~Checkbox();
    
    virtual void draw() override;

    virtual bool mouseClickEvent(glm::vec2 localPosition, Iyathuum::Key button) override;

    virtual void mouseEnterEvent() override;
    virtual void mouseLeaveEvent() override;

    void setText(std::string t);
    void setTextSize(float size);

    void setChecked(bool value);
    bool isChecked();
  private:
    std::string               _name;
    std::function<void(bool)> _clickedFunction;
    bool                      _checked = false;


    float _textSize = 1;
    bool _hovered = false;
  };
}