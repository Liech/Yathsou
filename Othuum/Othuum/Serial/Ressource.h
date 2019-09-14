#pragma once

#include <array>
#include "../Lib/nop/structure.h"
#include "Vector3.h"
#include "Quaternion.h"
#include "../Architecture/Decisions.h"
#include "Entity.h"
#include "Destructible.h"

//this includes debris, rocks, trees
namespace Serial {
  struct Ressource : Entity, Destructible{
    std::array<size_t, Decisions::numberOfRessources()> ressources;

    NOP_STRUCTURE(Ressource, position,orientation,modelID, ressources,health,landscapeID);
  };
}