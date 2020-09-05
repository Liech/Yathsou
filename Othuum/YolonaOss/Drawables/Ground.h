#pragma once

#include "../OpenGL/Drawable.h"

namespace YolonaOss
{
  class Ground : public GL::Drawable
  {
  public:
    Ground();
    ~Ground();

    virtual void load(GL::DrawSpecification*) override;
    virtual void draw() override;
  };
}