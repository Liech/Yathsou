#include "Units.h"

#include "SelenNavigationLib/Maps/DirectDistanceMap.h"


namespace Superb {
  Units::Units() {
    _map = std::make_shared<Selen::DirectDistanceMap<3>>();
    auto firstUnit = std::make_shared<Selen::NavigationAgent<3>>(std::array<double,3>{0.0,0.0,0.0},std::array<double,3>{0.0,0.0,0.0});
    _units.push_back(firstUnit);
  }

}