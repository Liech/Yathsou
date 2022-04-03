#include "Background.h"

#include "glad/glad.h"

namespace Ahwassa {
  Background::Background(Window* w) : Drawable(w),
    _color(0.2f*255, 0.3f*255, 0.3f*255)
  {
  }

  Background::~Background()
  {
  }

  void Background::setColor(const Iyathuum::Color& clr) {
    _color = clr;
  }

  Iyathuum::Color Background::getColor() const {
    return _color;
  }

  void Background::draw()
  {
    glClearColor(_color[0] / 255.0f, _color[1] / 255.0f, _color[2] / 255.0f,1);
    glClear(GL_COLOR_BUFFER_BIT);
  }
}