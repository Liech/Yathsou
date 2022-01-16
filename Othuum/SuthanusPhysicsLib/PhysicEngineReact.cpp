#include "PhysicEngineReact.h"

#include "Objects/SphereReact.h"

#include <reactphysics3d/reactphysics3d.h>

namespace Suthanus {
  class PhysicEngineReact::pimpl {
  public:
    reactphysics3d::PhysicsCommon common;
    reactphysics3d::PhysicsWorld* world;
  };

  PhysicEngineReact::PhysicEngineReact() {
    _pimpl        = std::make_unique<pimpl>();
    _pimpl->world = _pimpl->common.createPhysicsWorld();
  }

  PhysicEngineReact::~PhysicEngineReact() {
  }

  void PhysicEngineReact::setTicksPerSecond(int amount) {
    _ticksPerSecond = amount;
  }

  void PhysicEngineReact::update() {
    _pimpl->world->update((double)_ticksPerSecond / 60.0);
  }

  std::shared_ptr<Sphere> PhysicEngineReact::newSphere(const glm::vec3& pos, float radius, bool isDynamic) {
    React::SphereReact* result = new React::SphereReact(*this, pos, radius, isDynamic);
    auto ptr = std::shared_ptr<Sphere>(dynamic_cast<Sphere*>(result));
    ptr->initialize(ptr);
    _allObjects[result] = ptr;
    return ptr;
  }

  reactphysics3d::PhysicsWorld& PhysicEngineReact::world() {
    return *_pimpl->world;
  }

  reactphysics3d::PhysicsCommon& PhysicEngineReact::common() {
    return _pimpl->common;
  }

}