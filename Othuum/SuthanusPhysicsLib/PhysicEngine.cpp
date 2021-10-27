#include "PhysicEngine.h"

#include <iostream>
#include <vector>

#include "lib/bullet/btBulletDynamicsCommon.h"
#include "BulletCollision/CollisionShapes/btBox2dShape.h"
#include "BulletCollision/CollisionDispatch/btGhostObject.h"

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
      std::shared_ptr<PhysicObject> aLock = ptrA->self().lock();
      std::shared_ptr<PhysicObject> bLock = ptrB->self().lock();
      ev e;
      e.A = aLock;
      e.B = bLock;
      if (e.A && e.B)
        events.push_back(e);
    }
    for (auto e : events)
    {
      e.A->collisionEvent(e.B);
      e.B->collisionEvent(e.A);

    }
  }

  std::vector<std::shared_ptr<PhysicObject>> PhysicEngine::insideSphere(const glm::vec3& origin, float radius) const {
    btSphereShape sphere(radius);
    return insideShape(origin, sphere);
  }

  std::vector<std::shared_ptr<PhysicObject>> PhysicEngine::insideShape(const glm::vec3& origin, btCollisionShape& shape) const {
    //https://www.executionunit.com/blog/2015/03/27/bullet-physics-query-objects-with-a-volume/
    std::vector<std::shared_ptr<PhysicObject>> result;

    btPairCachingGhostObject volume;
    btTransform xform;
    xform.setOrigin(btVector3(origin[0], origin[1], origin[2]));
    volume.setCollisionShape(&shape);
    volume.setWorldTransform(xform);
    volume.setUserPointer(&result);
    volume.setCollisionFlags(volume.getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);

    struct ContactResultCallbackImpl : btCollisionWorld::ContactResultCallback {
      btScalar addSingleResult(btManifoldPoint& cp, const btCollisionObjectWrapper* colObj0Wrap, int partId0, int index0, const btCollisionObjectWrapper* colObj1Wrap, int partId1, int index1) override {
        colObj0Wrap->getCollisionObject()->getUserPointer();
        std::vector<std::shared_ptr<PhysicObject>>* resultLink = (std::vector<std::shared_ptr<PhysicObject>>*)colObj0Wrap->getCollisionObject()->getUserPointer();
        PhysicObject* obj = (PhysicObject*)colObj1Wrap->getCollisionObject()->getUserPointer();
        std::shared_ptr<PhysicObject> lock = obj->self().lock();
        resultLink->push_back(lock);
        return 0;
      }
    };

    ContactResultCallbackImpl cr;
    _world->contactTest(&volume, cr);
    return result;
  }
}