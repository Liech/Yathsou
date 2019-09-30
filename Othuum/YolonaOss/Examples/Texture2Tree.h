#pragma once

#include "../OpenGL/Drawable.h"
#include "../structs/MultiDimensionalArray.h"
#include <memory>

namespace YolonaOss {
  namespace GL {
    class DrawSpecification;
  }
  class Texture2Tree : public GL::Drawable {
    // Geerbt über Drawable
  public:
    virtual void load(GL::DrawSpecification*) override;
    virtual void draw() override;

  private:
    std::unique_ptr<MultiDimensionalArray<bool, 2>> _map;
  };
}