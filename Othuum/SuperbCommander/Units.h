#pragma once

#include <vector>
#include <map>

#include "SelenNavigationLib/NavigationAgent.h"
#include "SelenNavigationLib/NavigationMap.h"
#include "Unit.h"

namespace Ahwassa {
  class Window;
}

namespace Suthanus {
  class PhysicEngine;
  class Box;
}

namespace Superb {
  class Units {
  public:
    Units(Ahwassa::Window* w);

    std::vector<std::shared_ptr<Unit>> select(glm::vec3 pos, glm::vec3 dir);
    std::vector<std::shared_ptr<Unit>> selectCameraRect(glm::vec2 rectangleStart, glm::vec2 rectangleEnd);

    void update();
    void draw();
    void debugDraw();
    
  private:

    std::map<std::shared_ptr<Suthanus::Box>,std::shared_ptr<Unit>>       _units    ;
    std::shared_ptr<Suthanus::PhysicEngine>  _selection;

    Ahwassa::Window* _window;
  };
}