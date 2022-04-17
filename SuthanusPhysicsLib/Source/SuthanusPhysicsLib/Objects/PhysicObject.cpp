#include "PhysicObject.h"

#include "PhysicEngine.h"

namespace Suthanus
{
  PhysicObject::PhysicObject(PhysicEngine& engine) : _engine(engine) {

  }

  void PhysicObject::setCollisionCallback(std::function<void(std::weak_ptr<PhysicObject>)> callback)
  {
    _collsionCallback = callback;
  }

  void PhysicObject::collisionEventFirstPass(std::weak_ptr<PhysicObject> other)
  {
    std::shared_ptr<PhysicObject> ptr = other.lock();
    if (ptr)
      _contacts.insert(ptr);
  }

  void PhysicObject::collisionEventSecondPass(std::weak_ptr<PhysicObject> other)
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

  void PhysicObject::clearContacts() {
    _contacts.clear();
  }

  const std::set<std::shared_ptr<PhysicObject>>& PhysicObject::currentContacts() const{
    return _contacts;
  }

  PhysicEngine& PhysicObject::engine() {
    return _engine;
  }
}