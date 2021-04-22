#pragma once

#include <string>
#include <functional>

#include "AhwassaGraphicsLib/Input/UIElement.h"
#include "AhwassaGraphicsLib/Drawables/Drawable.h"

namespace Ahwassa {
  class Slider : public UIElement, public Drawable
  {
  public:
    Slider(Window*);
    Slider(Iyathuum::glmAABB<2> position, float min, float max, float startValue, std::function<void(float)> valueChangedCall, Window* w, UIElement* parent = nullptr);
    ~Slider();

    virtual void draw() override;

    virtual void mouseEnterEvent() override;
    virtual void mouseLeaveEvent() override;
    virtual bool mouseMoveEvent(glm::vec2 current, glm::vec2 movement) override;
    virtual bool mouseEvent(glm::vec2 localPosition, Iyathuum::Key button, Iyathuum::KeyStatus status) override;

    float getValue() { return _currentValue; }
    void   setValue(float value, bool emit = true);

  private:
    Iyathuum::glmAABB<2> getSliderLocation();
    Iyathuum::glmAABB<2> getBarLocation();

    const float leftPad = 0.05f;
    const float rightPad = 0.05f;
    const float barHeight = 0.3f;
    const float sliderHeight = 0.6f;
    const float sliderWidth = 0.1f;
    const float minSliderWidth = 15;


    std::function<void(float)> _valueChangedCall;
    float                      _min          = 0;
    float                      _max          = 1;
    float                      _currentValue = 0;

    bool _pressed = false;
    bool _hovered = false;
  };
}