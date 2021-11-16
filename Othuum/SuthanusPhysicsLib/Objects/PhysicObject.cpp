#include "PhysicObject.h"

#include <stdexcept>

namespace Suthanus
{
  PhysicObject::~PhysicObject() {
    if (!isDisposed())
      throw std::runtime_error("Dispose not called");
  }

  void PhysicObject::setCollisionCallback(std::function<void(std::weak_ptr<PhysicObject>)> callback)
  {
    _collsionCallback = callback;
  }

  void PhysicObject::collisionEvent(std::weak_ptr<PhysicObject> other)
  {
    _collsionCallback(other);
  }

  void PhysicObject::initialize(std::weak_ptr<PhysicObject> self)
  {
    _self = self;
  }

  glm::mat4 PhysicObject::getRotationTransformation() const
  {
    glm::mat4 trans = getTransformation();
    trans[3] = glm::vec4(0, 0, 0, 1);
    return trans;
  }

  void PhysicObject::dispose() {
    _deleted = true;
  }

  bool PhysicObject::isDisposed() const{
    return _deleted;
  }
}