#include "PhysicObject.h"

namespace Suthanus
{
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
}