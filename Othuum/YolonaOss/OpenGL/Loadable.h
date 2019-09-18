#pragma once

#include "DrawSpecification.h"

class Loadable {
public:
  Loadable() {}
  virtual ~Loadable() {}
  virtual void load(DrawSpecification*) = 0;
};