#pragma once

#include "OpenGL/DrawSpecification.h"

class Drawable
{
public:
  Drawable();
  ~Drawable();

  virtual void load(DrawSpecification*) = 0;
  virtual void draw() = 0;
};

