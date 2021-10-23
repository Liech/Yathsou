#pragma once

#include <vector>
#include "SelenNavigationLib/NavigationAgent.h"
#include "SelenNavigationLib/NavigationMap.h"


namespace Superb {
  class Units {
  public:
    Units();

  private:
    std::vector<std::shared_ptr<Selen::NavigationAgent<3>>>   _units;
    std::shared_ptr<Selen::NavigationMap<3>>                  _map  ;
  };
}