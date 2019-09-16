#pragma once

#include "../OpenGL/Drawable.h"

class Button : public Drawable
{
public:
  Button();
  ~Button();

  // Inherited via Drawable
  virtual void load(DrawSpecification*) override;
  virtual void draw() override;
};

