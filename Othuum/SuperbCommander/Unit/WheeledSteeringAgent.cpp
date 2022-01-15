#include "WheeledSteeringAgent.h"

#include "Unit.h"

namespace Superb {
  WheeledSteeringAgent::WheeledSteeringAgent(){

  }

  void WheeledSteeringAgent::setTarget(Unit* target) {
    _target = target;
  }

  void WheeledSteeringAgent::update() {

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
    return 1;
  }

  float WheeledSteeringAgent::getBreakSpeed() const {
    return 1;
  }

}