#pragma once

#include "SelenNavigationLib/NavigationAgent.h"
#include "SelenNavigationLib/NavigationMap.h"
#include <memory>

namespace Suthanus {
  class Box;
}

namespace Superb {
  class Unit {

  public:
    std::shared_ptr<Selen::NavigationAgent<3>> agent;
    std::shared_ptr<Suthanus::Box>             selector;
    std::shared_ptr<Selen::NavigationMap<3>>   map;
  };
}