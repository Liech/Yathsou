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
    Slider(Iyathuum::glmAABB<2> position, double min, double max, double startValue, std::function<void(double)> valueChangedCall, Window* w, UIElement* parent = nullptr);
    ~Slider();

    virtual void draw() override;

    virtual void mouseEnterEvent() override;
    virtual void mouseLeaveEvent() override;
    virtual bool mouseMoveEvent(glm::vec2 current, glm::vec2 movement) override;
    virtual bool mouseEvent(glm::vec2 localPosition, Iyathuum::Key button, Iyathuum::KeyStatus status) override;

    double getValue() { return _currentValue; }
    void   setValue(double value, bool emit = true);
    virtual void setVisible(bool visible) override;

  private:
    Iyathuum::glmAABB<2> getSliderLocation();
    Iyathuum::glmAABB<2> getBarLocation();

    const float leftPad = 0.4f;
    const float rightPad = 0.05f;
    const float barHeight = 0.3f;
    const float sliderHeight = 0.6f;
    const float sliderWidth = 0.1f;
    const float minSliderWidth = 15;


    std::function<void(double)> _valueChangedCall;
    double                      _min          = 0;
    double                      _max          = 1;
    double                      _currentValue = 0;

    bool _pressed = false;

    bool _hovered = false;
  };
}