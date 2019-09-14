#pragma once

#include "../Lib/nop/structure.h"
#include <map>
#include "Player.h"
#include "Ressource.h"
#include "ConstructionSite.h"
#include "Projectile.h"
#include "Unit.h"
#include "Building.h"
#include "ExtractionPoint.h"
#include "Landscape.h"
#include <memory>
namespace Serial {
  struct Gamestate {
    //general
    std::map<size_t, Player>           player;
    std::map<size_t, Ressource>        ressources;
    std::vector<Projectile>            projectiles;
    std::map<size_t, ExtractionPoint>  extractionPoints;
    std::map<size_t, Landscape>        Landscapes;

    //highly mutable
    std::map<size_t, std::shared_ptr<Entity>> units;

    NOP_STRUCTURE(Gamestate, player, ressources, projectiles, extractionPoints);
  };
}
