#include "Terrain.h"

#include "Database.h"
#include "Physic.h"

#include "SuperbCommander/World.h"
#include "AthanahCommonLib/Map/Map.h"


namespace Superb {
  Terrain::Terrain(Physic& physic, Database& database) {
    auto map = std::make_shared<Athanah::Map>(database.supComPath() + "\\" + "maps", "SCMP_009");
    _world = std::make_unique<Superb::World>(physic.physic(), map, database.gamedata());
  }

  void Terrain::menu() {

  }

  void Terrain::update() {
    _world->update();
  }

  World& Terrain::world() {
    return *_world;
  }

}