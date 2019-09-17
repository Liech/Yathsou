#pragma once

#include "DrawSpecification.h"

class Drawable
{
public:
  Drawable() {}
  virtual ~Drawable() {}

  virtual void load(DrawSpecification*) = 0;
  virtual void draw() = 0;
};

