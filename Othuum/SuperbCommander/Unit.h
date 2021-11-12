#pragma once

#include <memory>
#include <string>

#include "SelenNavigationLib/NavigationAgent.h"
#include "SelenNavigationLib/NavigationMap.h"
#include "AthanahCommonLib/SupCom/Blueprint/Blueprint.h"

namespace Suthanus {
  class Box;
}

namespace Superb {
  class Unit {

  public:
    std::shared_ptr<Selen::NavigationAgent<3>> agent   ;
    std::shared_ptr<Suthanus::Box>             selector;
    std::shared_ptr<Suthanus::Box>             physicBox;
    std::shared_ptr<Selen::NavigationMap<3>>   map     ;
    std::shared_ptr<const Athanah::Blueprint>  blueprint;
    std::string                                blueprintID = "UEL0201";
  };
}