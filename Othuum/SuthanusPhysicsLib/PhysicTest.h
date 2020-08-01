#pragma once

#include <array>

class btBroadphaseInterface;
class btDefaultCollisionConfiguration;
class btCollisionDispatcher;
class btSequentialImpulseConstraintSolver;
class btDiscreteDynamicsWorld;
class btRigidBody;

namespace Suthanus
{
  class PhysicTest
  {
  public:
    PhysicTest();
    void go();
    void update();
    std::array<float, 3> getPosition();

    btBroadphaseInterface               * _broadphase            ;
    btDefaultCollisionConfiguration     * _collisionConfiguration;
    btCollisionDispatcher               * _dispatcher            ;
    btSequentialImpulseConstraintSolver * _solver                ;
    btDiscreteDynamicsWorld             * _world                 ;
    btRigidBody                         * _body                  ;
  };
}