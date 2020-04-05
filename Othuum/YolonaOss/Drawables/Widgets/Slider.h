#pragma once

#include "Widget.h"
#include <string>
#include <functional>

namespace YolonaOss {
  namespace Widgets {
    class Slider : public Widget
    {
    public:
      Slider();
      Slider(std::string name, BoundingBox2 position, double min, double max, double startValue, std::function<void(double)> valueChangedCall);
      ~Slider();

      // Inherited via Drawable
      virtual void load(GL::DrawSpecification*) override;
      virtual void draw() override;

      virtual void mouseEnter() override;
      virtual void mouseLeave() override;
      virtual void mouseMove(glm::vec2 position) override;
      virtual bool mouseStatusChanged(glm::vec2 position, GL::Key k, GL::KeyStatus status) override;

    private:
      BoundingBox2 getSliderLocation();
      BoundingBox2 getBarLocation();

      const float leftPad      = 0.4f;
      const float rightPad     = 0.05f;
      const float barHeight    = 0.3f;
      const float sliderHeight = 0.6f;
      const float sliderWidth  = 0.1f;
      const float minSliderWidth = 15;


      std::string                 _name;
      std::function<void(double)> _valueChangedCall;
      double                      _min;
      double                      _max;
      double                      _currentValue;

      bool _pressed = false;

      bool _hovered = false;
    };
  }
}