#include "Units.h"

#include "SelenNavigationLib/Maps/DirectDistanceMap.h"
#include "SelenNavigationLib/Maps/AligmentMap.h"
#include "SelenNavigationLib/Maps/ComfortMap.h"
#include "SelenNavigationLib/Maps/DijkstraMap.h"
#include "SelenNavigationLib/Maps/DiscomfortMap.h"
#include "SelenNavigationLib/Maps/GradientGridMap.h"
#include "SelenNavigationLib/Maps/InfectiousArrivalMapGroup.h"
#include "SelenNavigationLib/NavigationAgentManager.h"
#include "SelenNavigationLib/MapGroup.h"


namespace Superb {
  Units::Units() {
    _map = std::make_shared<Selen::DirectDistanceMap<3>>();
    auto firstUnit = std::make_shared<Selen::NavigationAgent<3>>(glm::vec3(0),glm::vec3(0));
    _units.push_back(firstUnit);

    std::shared_ptr<Selen::AligmentMap<3>> m1;
    std::shared_ptr<Selen::ComfortMap<3>> m2;
    std::shared_ptr<Selen::DijkstraMap<3>> m3;
    std::shared_ptr<Selen::DiscomfortMap<3>> m4;
    std::shared_ptr<Selen::GradientGridMap<3>> m5;
    std::shared_ptr<Selen::InfectiousArrivalMapGroup<3>> m6;
    std::shared_ptr<Selen::NavigationAgentManager<3>> m7;
    std::shared_ptr<Selen::MapGroup<3>> m8;

  }

}