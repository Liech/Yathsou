#pragma once

#include "../Lib/nop/structure.h"
#include "Vector3.h"
#include "Owned.h"
#include "Entity.h"
#include "../Architecture/Decisions.h"
#include <array>
#include "Destructible.h"

namespace Serial {
  struct ConstructionSite : Entity, Owned, Destructible {
    std::array<size_t, Decisions::numberOfRessources()> neededRessources;    

    NOP_STRUCTURE(ConstructionSite, position, orientation,modelID,ownerID, health,neededRessources);
  };
}