#pragma once

#include "DrawSpecification.h"
#include "Loadable.h"
namespace YolonaOss {
  namespace GL {
    class Updateable : public Loadable
    {
    public:
      Updateable() {}
      virtual ~Updateable() {}

      virtual void load(DrawSpecification*) = 0;
      virtual void update() = 0;
    };
  }
}