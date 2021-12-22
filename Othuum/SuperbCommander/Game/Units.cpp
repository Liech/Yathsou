#include "Units.h"

#include "Database.h"
#include "Physic.h"
#include "SuperbCommander/UnitsOld.h"

namespace Superb {
  Units::Units(Physic& physic, Database& database) : _physic(physic),_database(database) {

  }

  void Units::update() {
    _units->update();
  }

  UnitsOld& Units::units() {
    return *_units;
  }

  void Units::save(nlohmann::json& output) {

  }

  void Units::load(nlohmann::json& input) {

  }

  void Units::start() {
    _units = std::make_unique<Superb::UnitsOld>(_database.gamedata(), _physic.physic());
  }
}