#pragma once

#include "VishalaNetworkLib/Core/SerializationGroup.h"

namespace Uyanah {
  namespace Commands {
    class Command : public Vishala::SerializationGroup<Command> {
    };
  }
}