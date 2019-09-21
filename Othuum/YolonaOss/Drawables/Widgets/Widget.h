#pragma once

#include "../../OpenGL/Drawable.h"
#include "../../OpenGL/Keys.h"
#include "../..//structs/BoundingBox.h"

class Widget : public Drawable {
public:
  Widget(BoundingBox2 position) {
    _position = position;
  }
  Widget() {
    _position = BoundingBox2(glm::vec2(0, 0), glm::vec2(100,100));
  }

  virtual void mouseEnter(){};
  virtual void mouseLeave(){};
  virtual void mouseClick(glm::vec2 position, Key k){};

  BoundingBox2 getPosition() const;
  void setPosition(BoundingBox2 pos);
private:
  BoundingBox2 _position;
};