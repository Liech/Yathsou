#include "Unit.h"

#include "UnitConstructor.h"

#include "SuthanusPhysicsLib/PhysicEngine.h"
#include "SuthanusPhysicsLib/Objects/Box.h"

namespace Superb {
  Unit::Unit(const UnitConstructor& info) {
    _physic    = info.getPhysic();
    _selector  = info.getSelector();
    _blueprint = info.getBlueprint();
    _id        = info.getId();
    placeOnGround();
  }

  glm::vec3 Unit::getPosition() const{
    return _physic->getPosition();
  }

  glm::mat4 Unit::getTransformation() const{
    return _physic->getTransformation();
  }

  std::shared_ptr<Suthanus::Box> Unit::getSelector() const{
    return _selector;
  }

  std::shared_ptr<Suthanus::Box> Unit::getPhysic() const{
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

  bool Unit::placeOnGround() {

    glm::vec3 groundNormal;
    glm::vec3 groundPos;
    if (nullptr == _physic->engine().raycast(getPosition(), glm::vec3(0, -60, 0), groundPos, groundNormal)) {
      return false;
    }
    
    glm::mat4 rotation = glm::rotate(glm::identity<glm::mat4>(), getRotation(), groundNormal);
    glm::vec4 r = glm::vec4(getForwardTangent(groundNormal), 1) * rotation;
    
    glm::vec3 x = getForwardTangent(groundNormal);
    glm::vec3 y = groundNormal;
    glm::vec3 z = getSidewardsTangent(groundNormal);
    
    glm::mat4 m = glm::mat4{
      x[0],x[1],x[2],0,
      y[0],y[1],y[2],0,
      z[0],z[1],z[2],0,
         0,   0,   0,1
    };
    
    glm::quat q = glm::quat_cast(m);
    _physic->setPosition(groundPos);
    _physic->setRotation(q);
    return true;
  }

  glm::vec3 Unit::getSidewardsTangent(glm::vec3 groundNormal) const {
    return glm::cross(glm::vec3(1, 0, 0), groundNormal);
  }

  glm::vec3 Unit::getForwardTangent(glm::vec3 groundNormal) const {
    return glm::cross(groundNormal, getSidewardsTangent(groundNormal));
  }

  float Unit::getRotation() const {
    return 0;
  }
}