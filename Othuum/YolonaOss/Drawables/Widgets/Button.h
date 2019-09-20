#pragma once

#include "Widget.h"
#include "glm/glm.hpp"
#include <string>
#include <functional>

class Button : public Widget
{
public:
  Button();
  Button(std::string name, glm::vec2 position, glm::vec2 size, std::function<void(void)> clickedFunction) {
    _position = position;
    _size     = size;
    _name     = name;
    _clickedFunction = clickedFunction;
  }
  ~Button();

  // Inherited via Drawable
  virtual void load(DrawSpecification*) override;
  virtual void draw() override;

  virtual void mouseEnter() override;
  virtual void mouseLeave() override;
  virtual void mouseClick(glm::vec2 position, MouseKey k) override;

private:
  glm::vec2                 _position;
  glm::vec2                 _size    ;
  std::string               _name    ;
  std::function<void(void)> _clickedFunction;

  bool _hovered = false;
};

