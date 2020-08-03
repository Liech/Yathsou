#pragma once

#include <array>
#include "IyathuumCoreLib/lib/glm/vec3.hpp"
#include <memory>
#include "Box.h"
#include "Sphere.h"

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

    std::shared_ptr<Box   > newBox   (glm::vec3 pos, glm::vec3 size  , bool isDynamic);
    std::shared_ptr<Sphere> newSphere(glm::vec3 pos, float     radius, bool isDynamic);

    btBroadphaseInterface               * _broadphase            ;
    btDefaultCollisionConfiguration     * _collisionConfiguration;
    btCollisionDispatcher               * _dispatcher            ;
    btSequentialImpulseConstraintSolver * _solver                ;
    btDiscreteDynamicsWorld             * _world                 ;
    btRigidBody                         * _body                  ;
  };
}