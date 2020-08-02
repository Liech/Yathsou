#pragma once

#include <array>
#include "IyathuumCoreLib/lib/glm/vec3.hpp"
#include <memory>
#include "Box.h"

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

    std::unique_ptr<Box> newBox(glm::vec3 pos);

    btBroadphaseInterface               * _broadphase            ;
    btDefaultCollisionConfiguration     * _collisionConfiguration;
    btCollisionDispatcher               * _dispatcher            ;
    btSequentialImpulseConstraintSolver * _solver                ;
    btDiscreteDynamicsWorld             * _world                 ;
    btRigidBody                         * _body                  ;
  };
}