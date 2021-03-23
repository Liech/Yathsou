#pragma once

#include "VishalaNetworkLib/Core/SerializationGroup.h"

namespace Uyanah {
  class Scene;
  namespace Commands {
    class Command : public Vishala::SerializationGroup<Command> {
    public:
      virtual void apply(Scene&) = 0;
    };
  }
}