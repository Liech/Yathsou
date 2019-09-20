#pragma once

#include "Widget.h"
#include "glm/glm.hpp"

class Menu : public Widget {
public:
  virtual void mouseEnter(){};
  virtual void mouseLeave(){};
  virtual void mouseClick(glm::vec2 position, MouseKey k){};
private:
};