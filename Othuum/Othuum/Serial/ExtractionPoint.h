#pragma once

#include "../Lib/nop/structure.h"
#include "Vector3.h"
#include "Quaternion.h"
#include "Entity.h"
#include <array>
#include "../Architecture/Decisions.h"

//this is for mass extraction points
namespace Serial {
  struct ExtractionPoint : Entity {
    std::array<size_t, Decisions::numberOfRessources()> ressourceExtractionPotential;

    NOP_STRUCTURE(ExtractionPoint, position, orientation, modelID, ressourceExtractionPotential);
  };
}