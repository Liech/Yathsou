#include "DriveInterface.h"
#include <iostream>
#include "Unit.h"
#include "SuthanusPhysicsLib/Objects/PhysicObject.h"

namespace Superb {
  DriveInterface::DriveInterface(Ahwassa::Input& input) : _input(input) {

  }

  void DriveInterface::update() {
    if (!_target)
      return;
    //if (_target->currentContacts().size() == 0)
    //  return;
    if (_input.getKeyStatus(Iyathuum::Key::KEY_UP) == Iyathuum::KeyStatus::PRESS) {
      //_target->setVelocity(_target->getRotationTransformation() * glm::vec4(0, 0, 4, 1));
      _target->move(glm::vec2(0.1f,0));
      std::cout << "UP" << std::endl;
    }
    if (_input.getKeyStatus(Iyathuum::Key::KEY_DOWN) == Iyathuum::KeyStatus::PRESS) {
      //_target->setVelocity(_target->getRotationTransformation() * glm::vec4(0, 0, -4, 1));
      _target->move(glm::vec2(-0.1f, 0));
      std::cout << "DOWN" << std::endl;
    }
    if (_input.getKeyStatus(Iyathuum::Key::KEY_RIGHT) == Iyathuum::KeyStatus::PRESS) {
      //_target->addForce(_target->getRotationTransformation() * glm::vec4(-0.03, 0, 0, 1), glm::vec3(0,0,0));
      _target->rotate(0.1);
      std::cout << "RIGHT" << std::endl;
    }
    if (_input.getKeyStatus(Iyathuum::Key::KEY_LEFT) == Iyathuum::KeyStatus::PRESS) {
      //_target->addForce(_target->getRotationTransformation() * glm::vec4(-0.03, 0, 0, 1), glm::vec3(0,0,0));
      _target->rotate(-0.1);
      std::cout << "LEFT" << std::endl;
    }
  }

  void DriveInterface::setTarget(std::shared_ptr<Unit> target) {
    _target = target;
  }
}