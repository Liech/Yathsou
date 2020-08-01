#include "PhysicTest.h"

#include <iostream>

#include "lib/bullet/btBulletDynamicsCommon.h"


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
    btAlignedObjectArray<btCollisionShape*> collisionShapes;

    btCollisionShape* groundShape = new btBoxShape(btVector3(btScalar(50.), btScalar(50.), btScalar(50.)));
    collisionShapes.push_back(groundShape);
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

      //btCollisionShape* colShape = new btBoxShape(btVector3(1,1,1));
      btCollisionShape* colShape = new btSphereShape(btScalar(1.));
      collisionShapes.push_back(colShape);

      /// Create Dynamic Objects
      btTransform startTransform;
      startTransform.setIdentity();

      btScalar mass(1.f);

      //rigidbody is dynamic if and only if mass is non zero, otherwise static
      bool isDynamic = (mass != 0.f);

      btVector3 localInertia(0, 0, 0);
      if (isDynamic)
        colShape->calculateLocalInertia(mass, localInertia);

      startTransform.setOrigin(btVector3(0, 0, 0));

      //using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
      btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
      btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, colShape, localInertia);
      _body = new btRigidBody(rbInfo);

      _world->addRigidBody(_body);
    }
  }
  void PhysicTest::update()
  {
    _world->stepSimulation(1.f / 1000.f, 10);
  }

  std::array<float, 3> PhysicTest::getPosition()
  {
    auto trans = _body->getWorldTransform().getOrigin();
    return { trans[0],trans[1],trans[2] };
  }


}