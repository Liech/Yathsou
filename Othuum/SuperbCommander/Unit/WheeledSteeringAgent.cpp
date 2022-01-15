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

  void WheeledSteeringAgent::debugDraw() {

  }

  void WheeledSteeringAgent::setDesiredDirection(const WheeledSteeringAgent::v3&) {

  }

  void WheeledSteeringAgent::setDesiredSpeed(float) {

  }

  WheeledSteeringAgent::v3 WheeledSteeringAgent::getCurrentDirection() const {
    return _target->getDirection();
  }

  float WheeledSteeringAgent::getMaximumSpeed() const {
    return 1;
  }

  float WheeledSteeringAgent::getBreakSpeed() const {
    return 1;
  }

}