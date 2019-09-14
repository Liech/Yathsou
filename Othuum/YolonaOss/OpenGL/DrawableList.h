#pragma once

#include "OpenGL/Drawable.h"
#include <vector>
#include <memory>

class DrawableList : public Drawable
{
public:
  DrawableList();
  ~DrawableList();

  void addDrawable(std::shared_ptr<Drawable> draw);
  virtual void load(DrawSpecification*) override;
  virtual void draw() override;

private:
  std::vector<std::shared_ptr<Drawable>> _drawables;
};
