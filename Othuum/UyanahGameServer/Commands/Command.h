#pragma once

#include "VishalaNetworkLib/Core/Serialization.h"

namespace Uyanah {
  class Scene;
  namespace Commands {
    class Command : public Vishala::Serialization {
    public:
      virtual void apply(Scene&) = 0;
    };
  }
}