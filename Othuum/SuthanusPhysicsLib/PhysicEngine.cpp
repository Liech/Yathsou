#include "PhysicEngine.h"

#include <iostream>
#include <vector>

#include "lib/bullet/btBulletDynamicsCommon.h"
#include "BoxBullet.h"
#include "SphereBullet.h"
#include "VehicleBulletRaycast.h"

namespace Suthanus
{
  PhysicEngine::PhysicEngine() :
    _broadphase(new btDbvtBroadphase())
    , _collisionConfiguration(new btDefaultCollisionConfiguration())
    , _dispatcher(new btCollisionDispatcher(_collisionConfiguration))
    , _solver(new btSequentialImpulseConstraintSolver())
    , _world(new btDiscreteDynamicsWorld(_dispatcher, new btDbvtBroadphase(), _solver, _collisionConfiguration))
  {

  }

  void PhysicEngine::debugDrawWorld() {
    _world->debugDrawWorld();
  }

  void PhysicEngine::setDebugDrawer(btIDebugDraw* drawer)
  {
    _world->setDebugDrawer(drawer);
  }

  void PhysicEngine::go()
  {
    _world->setGravity(btVector3(0, -10, 0));
  }

  void PhysicEngine::update()
  {
    _world->stepSimulation(1.f / 10.f, 1);
    handleCollision();
  }

  std::shared_ptr<Box> PhysicEngine::newBox(glm::vec3 pos, glm::vec3 size, bool isDynamic)
  {
    Bullet::BoxBullet* result = new Bullet::BoxBullet(_world, pos, size, isDynamic);
    std::shared_ptr<Box> ptr =  std::shared_ptr<Box>(dynamic_cast<Box*>(result));
    ptr->initialize(ptr);
    return ptr;
  }

  std::shared_ptr<Sphere> PhysicEngine::newSphere(glm::vec3 pos, float radius, bool isDynamic)
  {
    Bullet::SphereBullet* result = new Bullet::SphereBullet(_world, pos, radius, isDynamic);
    auto ptr = std::shared_ptr<Sphere>(dynamic_cast<Sphere*>(result));
    ptr->initialize(ptr);
    return ptr;
  }

  std::shared_ptr<Vehicle> PhysicEngine::newVehicle(glm::vec3 pos)
  {
    Bullet::VehicleBulletRaycast* result = new Bullet::VehicleBulletRaycast(_world, pos);
    auto ptr =  std::shared_ptr<Vehicle>(dynamic_cast<Vehicle*>(result));
    ptr->initialize(ptr);
    return ptr;
  }

  void PhysicEngine::handleCollision()
  {
    struct ev
    {
      std::shared_ptr<PhysicObject> A;
      std::shared_ptr<PhysicObject> B;
    };
    std::vector<ev> events;
    btDispatcher* dp = _world->getDispatcher();
    const int numManifolds = dp->getNumManifolds();
    for (int m = 0; m < numManifolds; ++m)
    {
      btPersistentManifold* man = dp->getManifoldByIndexInternal(m);
      const btRigidBody* obA = static_cast<const btRigidBody*>(man->getBody0());
      const btRigidBody* obB = static_cast<const btRigidBody*>(man->getBody1());
      PhysicObject* ptrA = (PhysicObject*)obA->getUserPointer();
      PhysicObject* ptrB = (PhysicObject*)obB->getUserPointer();
      // use user pointers to determine if objects are eligible for destruction.
      std::shared_ptr<PhysicObject> aLock = ptrA->self().lock();
      std::shared_ptr<PhysicObject> bLock = ptrB->self().lock();
      ev e;
      e.A = aLock;
      e.B = bLock;
      if (e.A && e.B)
        events.push_back(e);
      //  const int numc = man->getNumContacts();
    //  float totalImpact = 0.0f;
    //  for (int c = 0; c < numc; ++c)
    //    totalImpact += man->getContactPoint(c).m_appliedImpulse;
    //  if (totalImpact > threshold)
    //  {
    //    // Here you can break one, or both shapes, if so desired.
    //  }
    }
    for (auto e : events)
    {
      e.A->collisionEvent(e.B);
      e.B->collisionEvent(e.A);
    }
  }
}