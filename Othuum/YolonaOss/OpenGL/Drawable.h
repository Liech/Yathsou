#pragma once

#include "DrawSpecification.h"
#include "Loadable.h"
namespace YolonaOss {
  namespace GL {
    class Drawable : public Loadable
    {
    public:
      Drawable() {}
      virtual ~Drawable() {}

      virtual void load(DrawSpecification*) = 0;
      virtual void draw() = 0;
    };
  }
}