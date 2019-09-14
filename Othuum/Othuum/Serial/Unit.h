#pragma once

#include "Lib/nop/structure.h"
#include "Vector3.h"
#include "MoveableEntity.h"
#include "Owned.h"
#include "Destructible.h"

namespace Serial {
  struct Unit : MoveableEntity, Owned, Destructible {
    
    NOP_STRUCTURE(Unit, position, orientation, velocity, modelID, ownerID, health);
  };
}