#include "Units.h"

#include "Database.h"
#include "Physic.h"
#include "SuperbCommander/UnitsOld.h"

namespace Superb {
  Units::Units(Physic& physic, Database& database) {
    _units = std::make_unique<Superb::UnitsOld>(database.gamedata(), physic.physic());

  }

  void Units::update() {
    _units->update();
  }

  UnitsOld& Units::units() {
    return *_units;
  }

}