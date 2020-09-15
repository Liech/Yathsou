#include "PhysicObject.h"

namespace Suthanus
{
  void PhysicObject::setCollisionCallback(std::function<void(PhysicObject*)> callback)
  {
    _collsionCallback = callback;
  }

  void PhysicObject::collisionEvent(PhysicObject* other)
  {
    _collsionCallback(other);
  }
}