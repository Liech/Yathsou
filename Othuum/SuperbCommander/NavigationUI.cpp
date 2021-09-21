#include "NavigationUI.h"

namespace Superb {
  NavigationUI::NavigationUI(Ahwassa::Window* w, std::shared_ptr<Suthanus::PhysicEngine> physic, std::shared_ptr<Suthanus::PhysicNavigationMesh> nav) {
    _window  = w     ;
    _physic  = physic;
    _navMesh = nav   ;
  }

  void NavigationUI::update() {

  }

  void NavigationUI::debugDraw() {

  }
}