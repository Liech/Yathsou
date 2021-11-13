#include "Unit.h"

#include "UnitConstructor.h"

#include "SuthanusPhysicsLib/Objects/Box.h"

namespace Superb {
  Unit::Unit(const UnitConstructor& info) {
    _physic   = info.getPhysic();
    _selector = info.getSelector();
  }

  glm::vec3 Unit::getPosition() {
    return _physic->getPosition();
  }

  std::shared_ptr<Suthanus::Box> Unit::getSelector() {
    return _selector;

  }
  void Unit::update() {
    _selector->setPosition(getPosition());
  }
}