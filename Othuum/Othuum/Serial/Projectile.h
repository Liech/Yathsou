#pragma once

#include "../Lib/nop/structure.h"
#include "Vector3.h"
#include "MoveableEntity.h"
#include "../Architecture/Decisions.h"
#include <array>
#include "Owned.h"
#include "Destructible.h"

namespace Serial {
  struct Projectile : MoveableEntity, Owned, Destructible{
    size_t impactID;

    NOP_STRUCTURE(Projectile, position, orientation, velocity, modelID, impactID, ownerID,health);
  };
}