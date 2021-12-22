#include "Terrain.h"

#include "Database.h"
#include "Physic.h"

#include "SuperbCommander/World.h"
#include "AthanahCommonLib/Map/Map.h"


namespace Superb {
  Terrain::Terrain(Physic& physic, Database& database) :_physic(physic),_database(database) {

  }

  void Terrain::menu() {

  }

  void Terrain::update() {
    _world->update();
  }

  World& Terrain::world() {
    return *_world;
  }

  void Terrain::save(nlohmann::json& output) {

  }

  void Terrain::load(nlohmann::json& input) {

  }

  void Terrain::start() {
    auto map = std::make_shared<Athanah::Map>(_database.supComPath() + "\\" + "maps", "SCMP_009");
    _world   = std::make_unique<Superb::World>(_physic.physic(), map, _database.gamedata());
  }
}