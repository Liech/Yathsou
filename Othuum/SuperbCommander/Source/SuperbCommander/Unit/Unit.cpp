#include "Unit/Unit.h"

#include "Unit/UnitConstructor.h"
#include "UnitAgentInterface.h"

#include "SuthanusPhysicsLib/PhysicEngine.h"
#include "SuthanusPhysicsLib/Objects/Box.h"

namespace Superb {
  Unit::Unit(const UnitConstructor& info) {
    _physic    = info.getPhysic();
    _selector  = info.getSelector();
    _blueprint = info.getBlueprint();
    _id        = info.getId();
    _agent     = info.getAgent();
    _agent->setTarget(this);
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
    if (hasCommand()) {
      if (_command->isFullfilled()) {
        _command->cleanup();
        _command = nullptr;
      }
      else
        _command->update();
    }
    _agent->update();
    _selector->setPosition(getPosition());
  }

  void Unit::debugDraw() {
    
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

    glm::vec3 x = getSidewards(groundNormal);
    glm::vec3 y = groundNormal;
    glm::vec3 z = getForwards(groundNormal);
    
    glm::mat4 m = glm::mat4{
      x[0],x[1],x[2],0,
      y[0],y[1],y[2],0,
      z[0],z[1],z[2],0,
         0,   0,   0,1
    };
    
    glm::quat q = glm::quat_cast(m);
    _physic->setPosition(groundPos + glm::vec3(0,getPhysic()->getSize()[1]/2.0f,0));
    _physic->setRotation(q);
    return true;
  }

  glm::vec3 Unit::getForwards(glm::vec3 groundNormal) const {
    return glm::cross(glm::vec3(std::cos(_rotation), 0, std::sin(_rotation)), groundNormal);
  }

  glm::vec3 Unit::getSidewards(glm::vec3 groundNormal) const {
    return glm::cross(groundNormal, getForwards(groundNormal));
  }

  float Unit::getRotation() const {
    return _rotation;
  }

  void Unit::move(const glm::vec2& position) {
    auto rot = getPhysic()->getRotation();
    glm::vec3 normal = glm::mat4_cast(rot) * glm::vec4(0, 1, 0, 1);
    _physic->setPosition(getPosition() + getSidewards(normal) * position[1] + getForwards(normal) * position[0]);
    placeOnGround();
  }

  void Unit::rotate(const float& radian) {
    _rotation = _rotation + radian;
    placeOnGround();
  }

  glm::vec3 Unit::getDirection() const {
    auto rot = getPhysic()->getRotation();
    return glm::mat4_cast(rot) * glm::vec4(0, 1, 0, 1);
  }

  UnitAgentInterface& Unit::agent() {
    return *_agent;
  }

  void Unit::setCommand(std::shared_ptr<Iyathuum::Command> command) {
    if (hasCommand())
      _command->cleanup();
    _command = command;
  }

  bool Unit::hasCommand() {
    return _command != nullptr;
  }

}