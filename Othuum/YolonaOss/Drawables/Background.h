#pragma once

#include "../OpenGL/Drawable.h"

//0: just a background color

namespace YolonaOss {
  class Background : public GL::Drawable
  {
  public:
    Background();
    ~Background();

    // Inherited via Drawable
    virtual void load(GL::DrawSpecification*) override;
    virtual void draw() override;

    glm::vec3 color;
  };
}