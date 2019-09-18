#pragma once

#include "../OpenGL/Drawable.h"
#include "glm/glm.hpp"
#include <string>

class Button : public Drawable
{
public:
  Button();
  Button(std::string name, glm::vec2 position, glm::vec2 size) {
    _position = position;
    _size     = size;
    _name     = name;
  }
  ~Button();

  // Inherited via Drawable
  virtual void load(DrawSpecification*) override;
  virtual void draw() override;



private:
  glm::vec2   _position;
  glm::vec2   _size;
  std::string _name;
};

