#pragma once

#include <vector>
#include <array>
#include "../Lib/nop/structure.h"
#include "Vector3.h"
#include "../Architecture/Decisions.h"

//to keep it leightweight the units of a player are stored in a different table
namespace Serial {
  struct Player {
    size_t                                             iD;
    std::vector<size_t>                                allies;
    std::array<size_t,Decisions::numberOfRessources()> ressources;

    NOP_STRUCTURE(Player, iD, allies, ressources);
  };
}