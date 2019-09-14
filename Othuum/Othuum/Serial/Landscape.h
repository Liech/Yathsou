#pragma once

#include "../Lib/nop/structure.h"
#include "Entity.h"

namespace Serial {
  struct Landscape : Entity{
    
    NOP_STRUCTURE(Landscape, position, orientation, modelID);
  };
}