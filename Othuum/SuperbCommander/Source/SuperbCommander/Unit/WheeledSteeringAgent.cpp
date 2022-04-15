#include "WheeledSteeringAgent.h"

#include <iostream>

#include <glm/gtx/vector_angle.hpp>
#include <IyathuumCoreLib/Util/Geometry.h>

#include <SuthanusPhysicsLib/Objects/Box.h>
#include "Unit.h"

namespace Superb {
  WheeledSteeringAgent::WheeledSteeringAgent(){

  }

  void WheeledSteeringAgent::setTarget(Unit* target) {
    _target = target;
  }

  void WheeledSteeringAgent::update() {
    if (glm::length(_desiredDirection) < 1e-5)
      return;
    auto current = glm::vec2(std::cos(_target->getRotation() + glm::pi<float>() / 2.0), std::sin(_target->getRotation() + glm::pi<float>() / 2.0));
    auto desired = glm::vec2(getDesiredDirection()[0], getDesiredDirection()[2]);
    float angleDiff = glm::orientedAngle(glm::normalize(current), glm::normalize(desired));
    _target->rotate(angleDiff / 15.0f);
    _target->move(glm::vec2(getDesiredSpeed(), 0));    
  }

  void WheeledSteeringAgent::setDesiredDirection(const WheeledSteeringAgent::v3& dir) {
    _desiredDirection = dir;
  }

  glm::vec3 WheeledSteeringAgent::getDesiredDirection() {
    return _desiredDirection;
  }

  void WheeledSteeringAgent::setDesiredSpeed(float speed) {
    _desiredSpeed = speed;
  }

  float WheeledSteeringAgent::getDesiredSpeed() {
    return _desiredSpeed;
  }

  WheeledSteeringAgent::v3 WheeledSteeringAgent::getDirection() const {
    return _target->getDirection();
  }

  WheeledSteeringAgent::v3 WheeledSteeringAgent::getPosition() const {
    return _target->getPosition();
  }

  float WheeledSteeringAgent::getMaximumSpeed() const {
    return 0.1f;
  }

  float WheeledSteeringAgent::getBreakSpeed() const {
    return 1;
  }

  std::array<float, 3> WheeledSteeringAgent::getSize() const {
    return {_target->getPhysic()->getSize()[0],_target->getPhysic()->getSize()[1],_target->getPhysic()->getSize()[2]};
  }
}