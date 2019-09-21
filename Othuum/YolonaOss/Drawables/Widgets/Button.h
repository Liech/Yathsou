#pragma once

#include "Widget.h"
#include <string>
#include <functional>

namespace YolonaOss {
  class Button : public Widget
  {
  public:
    Button();
    Button(std::string name, BoundingBox2 position, std::function<void(void)> clickedFunction) : Widget(position) {
      _clickedFunction = clickedFunction;
      _name = name;
    }
    ~Button();

    // Inherited via Drawable
    virtual void load(GL::DrawSpecification*) override;
    virtual void draw() override;

    virtual void mouseEnter() override;
    virtual void mouseLeave() override;
    virtual void mouseClick(glm::vec2 position, GL::Key k) override;

  private:
    std::string               _name;
    std::function<void(void)> _clickedFunction;

    bool _hovered = false;
  };
}