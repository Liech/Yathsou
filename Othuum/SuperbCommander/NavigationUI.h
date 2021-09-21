#pragma once

#include <memory>

namespace Ahwassa {
  class Window;
}

namespace Suthanus {
  class PhysicEngine;
  class PhysicNavigationMesh;
}

//window, physic, navmesh
namespace Superb {
  class NavigationUI {
  public:
    NavigationUI(Ahwassa::Window* w, std::shared_ptr<Suthanus::PhysicEngine>, std::shared_ptr<Suthanus::PhysicNavigationMesh>);

    void update();
    void debugDraw();
  private:
    Ahwassa::Window*                                _window ;
    std::shared_ptr<Suthanus::PhysicEngine>         _physic ;
    std::shared_ptr<Suthanus::PhysicNavigationMesh> _navMesh;
  };
}