#pragma once

#include "../OpenGL/Drawable.h"

//0: just a background color

class Background : public Drawable
{
public:
  Background();
  ~Background();

  // Inherited via Drawable
  virtual void load(DrawSpecification*) override;
  virtual void draw() override;
};

