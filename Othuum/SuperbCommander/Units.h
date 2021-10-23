#pragma once

#include <vector>
#include "SelenNavigationLib/NavigationAgent.h"
#include "SelenNavigationLib/NavigationMap.h"


namespace Ahwassa {
  class Window;
}

namespace Superb {
  class Units {
  public:
    Units(Ahwassa::Window* w);

    void setTarget(glm::vec3);

    void update();
    void draw();
    void debugDraw();
  private:
    std::vector<std::shared_ptr<Selen::NavigationAgent<3>>>   _units;
    std::shared_ptr<Selen::NavigationMap<3>>                  _map;

    Ahwassa::Window* _window;
  };
}