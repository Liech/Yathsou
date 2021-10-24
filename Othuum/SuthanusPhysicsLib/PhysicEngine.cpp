#include "PhysicEngine.h"

#include <iostream>
#include <vector>

#include "lib/bullet/btBulletDynamicsCommon.h"
#include "Objects/BoxBullet.h"
#include "Objects/SphereBullet.h"
#include "Objects/VehicleBulletRaycast.h"
#include "Objects/HeightMapBullet.h"

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

  void PhysicEngine::setTicksPerSecond(int amount)
  {
    _physicTicksPerSecond = amount;
  }

  void PhysicEngine::setDebugDrawer(btIDebugDraw* drawer)
  {
    _world->setDebugDrawer(drawer);
  }

  void PhysicEngine::go()
  {
    _world->setGravity(btVector3(0, -9.81, 0));
  }

  std::shared_ptr<PhysicObject> PhysicEngine::raycast(const glm::vec3& origin, const glm::vec3& direction, glm::vec3& hitPoint) const
  {
    btVector3 bOrigin   (origin.x, origin.y, origin.z);
    btVector3 bDirection(direction.x, direction.y, direction.z);
    btVector3 bTarget = bOrigin + bDirection * 1000;
    glm::vec3 target(bTarget.x(), bTarget.y(), bTarget.z());
    btCollisionWorld::ClosestRayResultCallback result(bOrigin, bTarget);
    _world->rayTest(bOrigin, bTarget, result);
    if (!result.hasHit()) {
      hitPoint = glm::vec3(0, 0, 0);
      return nullptr;
    }
    else
    {
      hitPoint = glm::vec3(result.m_hitPointWorld.x(), result.m_hitPointWorld.y(), result.m_hitPointWorld.z());
      PhysicObject* ptr = (PhysicObject*)result.m_collisionObject->getUserPointer();
      if (!ptr)
        return nullptr;
      return ptr->self().lock();
    }    
  }

  std::set<std::shared_ptr<PhysicObject>> PhysicEngine::cameraCast(const glm::vec3& origin, const glm::vec3& direction1, const glm::vec3& direction2) const {
    //glm::vec3 dir1 = glm::normalize(direction1);
    //glm::vec3 dir2 = glm::normalize(direction2);
    //glm::vec3 rectPos1 = origin + dir1 * 0.1f;
    //glm::vec3 rectPos2 = origin + dir1 * 0.1f;
    //
    //
    //btBoxShape boxShape(btVector3(1,1,1));
    //btTransform from;
    

    //btTransform to;
    //_world->convexSweepTest(&boxShape,from,to,)
    //
    //  tsFrom = TransformState.makePos(Point3(0, 0, 0))
    //  tsTo = TransformState.makePos(Point3(10, 0, 0))
    //
    //  shape = BulletSphereShape(0.5)
    //  penetration = 0.0
    //
    //  result = world.sweepTestClosest(shape, tsFrom, tsTo, penetration)
    return {};
  }

  void PhysicEngine::update()
  {
    _world->stepSimulation(1.f / _physicTicksPerSecond, 1);
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

  std::shared_ptr<HeightMap> PhysicEngine::newHeightMap(glm::vec3 pos, const Iyathuum::MultiDimensionalArray<unsigned short, 2>& content, float height)
  {
    glm::vec2 cellSize(1,1);
    Bullet::HeightMapBullet* result = new Bullet::HeightMapBullet(_world, pos, cellSize, content,height);
    auto ptr = std::shared_ptr<HeightMap>(dynamic_cast<HeightMap*>(result));
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
      //std::cout << "Collision" << std::endl;
      e.A->collisionEvent(e.B);
      e.B->collisionEvent(e.A);

    }
  }
}