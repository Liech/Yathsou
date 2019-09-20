#pragma once

#include "../../OpenGL/Drawable.h"
#include "../../OpenGL/Keys.h"
#include "glm/glm.hpp"

class Widget : public Drawable {
public:
  virtual void mouseEnter(){};
  virtual void mouseLeave(){};
  virtual void mouseClick(glm::vec2 position, MouseKey k){};
private:
};