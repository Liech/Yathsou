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
    Button(std::string name, Iyathuum::glmAABB<2> position, std::function<void(void)> clickedFunction, Window* w, UIElement* parent = nullptr);
    ~Button();
    
    virtual void draw() override;

    virtual bool mouseClickEvent(glm::vec2 localPosition, Iyathuum::Key button) override;

    virtual void mouseEnterEvent() override;
    virtual void mouseLeaveEvent() override;

    void setDrawOverride(std::function<void(Iyathuum::glmAABB<2>, bool hovered)> overrideCall);

    void setText(std::string t);
    void setTextSize(float size);
  private:
    std::string               _name;
    std::function<void(void)> _clickedFunction;

    float _textSize = 1;
    bool _hovered = false;
    bool _drawOverrideEnabled = false;
    std::function<void(Iyathuum::glmAABB<2>, bool hovered)> _drawOverride;

  };
}