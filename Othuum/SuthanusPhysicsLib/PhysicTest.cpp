#include "PhysicTest.h"

#include <iostream>

#include "lib/bullet/btBulletDynamicsCommon.h"
#include "BoxBullet.h"
#include "SphereBullet.h"
#include "VehicleBulletRaycast.h"

namespace Suthanus
{
  PhysicTest::PhysicTest() :
      _broadphase            (new btDbvtBroadphase               ())
    , _collisionConfiguration(new btDefaultCollisionConfiguration())
    , _dispatcher            (new btCollisionDispatcher          (_collisionConfiguration))
    , _solver                (new btSequentialImpulseConstraintSolver())
    , _world                 (new btDiscreteDynamicsWorld(_dispatcher, new btDbvtBroadphase(), _solver, _collisionConfiguration))
  {
  }

  void PhysicTest::debugDrawWorld() {
    _world->debugDrawWorld();
  }

  void PhysicTest::setDebugDrawer(btIDebugDraw* drawer)
  {
    _world->setDebugDrawer(drawer);
  }

  void PhysicTest::go()
  {
    _world->setGravity(btVector3(0, -10, 0));
  }
  void PhysicTest::update()
  {
    _world->stepSimulation(1.f / 1000.f, 10);

  }
  

  std::shared_ptr<Box> PhysicTest::newBox(glm::vec3 pos, glm::vec3 size, bool isDynamic)
  {
    Bullet::BoxBullet* result = new Bullet::BoxBullet(_world, pos, size, isDynamic);

    return std::shared_ptr<Box>(dynamic_cast<Box*>(result));
  }

  std::shared_ptr<Sphere> PhysicTest::newSphere(glm::vec3 pos, float radius, bool isDynamic)
  {
    Bullet::SphereBullet* result = new Bullet::SphereBullet(_world, pos, radius, isDynamic);
    return std::shared_ptr<Sphere>(dynamic_cast<Sphere*>(result));
  }

  std::shared_ptr<Vehicle> PhysicTest::newVehicle(glm::vec3 pos)
  {
    Bullet::VehicleBulletRaycast* result = new Bullet::VehicleBulletRaycast(_world, pos);
    return std::shared_ptr<Vehicle>(dynamic_cast<Vehicle*>(result));
  }
}