#include "Unit.h"

#include "UnitConstructor.h"

#include "SuthanusPhysicsLib/Objects/Box.h"

namespace Superb {
  Unit::Unit(const UnitConstructor& info) {
    _physic    = info.getPhysic();
    _selector  = info.getSelector();
    _blueprint = info.getBlueprint();
    _id        = info.getId();
  }

  glm::vec3 Unit::getPosition() {
    return _physic->getPosition();
  }

  glm::mat4 Unit::getTransformation() {
    return _physic->getTransformation();
  }

  std::shared_ptr<Suthanus::Box> Unit::getSelector() {
    return _selector;
  }

  std::shared_ptr<Suthanus::Box> Unit::getPhysic() {
    return _physic;
  }

  void Unit::update() {
    _selector->setPosition(getPosition());
  }

  std::shared_ptr<const Athanah::Blueprint> Unit::getBlueprint() const {
    return _blueprint;
  }

  std::string Unit::getID() const {
    return _id;
  }

}