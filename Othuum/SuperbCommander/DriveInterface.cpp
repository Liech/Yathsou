#include "DriveInterface.h"

#include "SuthanusPhysicsLib/Objects/PhysicObject.h"

namespace Superb {
  DriveInterface::DriveInterface(Ahwassa::Input& input) : _input(input) {

  }

  void DriveInterface::update() {
    if (!_target)
      return;

    if (_input.getKeyStatus(Iyathuum::Key::KEY_SPACE) == Iyathuum::KeyStatus::PRESS) {
      _target->setVelocity(glm::vec3(0, 4, 0));
    }
    if (_input.getKeyStatus(Iyathuum::Key::KEY_UP) == Iyathuum::KeyStatus::PRESS) {
      _target->setVelocity(_target->getRotationTransformation() * glm::vec4(0, 0, 4, 1));
    }
  }

  void DriveInterface::setTarget(std::shared_ptr<Suthanus::PhysicObject> target) {
    _target = target;
  }
}