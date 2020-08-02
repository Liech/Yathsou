#include "PhysicTest.h"

#include <iostream>

#include "lib/bullet/btBulletDynamicsCommon.h"
#include "BoxBullet.h"

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

  void PhysicTest::go()
  {
    std::cout << "Huhu" << std::endl;
    //New variables

    _world->setGravity(btVector3(0, -10, 0));

    btCollisionShape* groundShape = new btBoxShape(btVector3(btScalar(50.), btScalar(50.), btScalar(50.)));
    btTransform groundTransform;
    groundTransform.setIdentity();
    groundTransform.setOrigin(btVector3(0, -2, 0));
    btScalar mass(1);
    bool isDynamic = (mass != 0.f);

    btVector3 localInertia(0, 0, 0);
    if (isDynamic)
      groundShape->calculateLocalInertia(mass, localInertia);


    {
      //create a dynamic rigidbody





      //using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects


    }
  }
  void PhysicTest::update()
  {
    _world->stepSimulation(1.f / 1000.f, 10);
  }


  std::unique_ptr<Box> PhysicTest::newBox(glm::vec3 pos)
  {     
    //btCollisionShape* colShape = new btBoxShape(btVector3(1,1,1));
    btCollisionShape* colShape = new btSphereShape(btScalar(1.));

    /// Create Dynamic Objects
    btTransform startTransform;
    startTransform.setIdentity();

    btScalar mass(1.f);

    //rigidbody is dynamic if and only if mass is non zero, otherwise static
    bool isDynamic = (mass != 0.f);

    btVector3 localInertia(0, 0, 0);
    if (isDynamic)
      colShape->calculateLocalInertia(mass, localInertia);

    startTransform.setOrigin(btVector3(pos[0],pos[1],pos[2]));
    btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
    btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, colShape, localInertia);

    _body = new btRigidBody(rbInfo);

    _world->addRigidBody(_body);
    BoxBullet* result = new BoxBullet(_body);

    return std::move(std::unique_ptr<Box>(dynamic_cast<Box*>(result)));
  }
}