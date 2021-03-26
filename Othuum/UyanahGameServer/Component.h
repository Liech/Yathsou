#pragma once

#include "VishalaNetworkLib/Core/Serialization.h"

namespace Uyanah {
  class Component : public Vishala::Serialization {
  public:
    virtual void update() { };
  };
}