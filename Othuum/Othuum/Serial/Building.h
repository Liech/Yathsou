#pragma once

#include "../Lib/nop/structure.h"
#include "Vector3.h"
#include "Entity.h"
#include "Owned.h"
#include "Destructible.h"

namespace Serial {
  struct Building : Entity, Owned, Destructible{
    
    NOP_STRUCTURE(Building, position, orientation, modelID, ownerID, health);
  };
}