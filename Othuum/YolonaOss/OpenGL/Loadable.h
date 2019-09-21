#pragma once

#include "DrawSpecification.h"
namespace YolonaOss {
  namespace GL {
    class Loadable {
    public:
      Loadable() {}
      virtual ~Loadable() {}
      virtual void load(DrawSpecification*) = 0;
    };
  }
}