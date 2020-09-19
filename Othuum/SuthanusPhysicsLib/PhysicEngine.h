#pragma once

#include <array>
#include "IyathuumCoreLib/lib/glm/vec3.hpp"
#include <memory>
#include "Box.h"
#include "Sphere.h"
#include "Vehicle.h"

class btBroadphaseInterface;
class btDefaultCollisionConfiguration;
class btCollisionDispatcher;
class btSequentialImpulseConstraintSolver;
class btDiscreteDynamicsWorld;
class btRigidBody;
class btIDebugDraw;

namespace Suthanus
{
  class PhysicEngine
  {
  public:
    PhysicEngine();
    void go();
    void update();
    void setTicksPerSecond(int amount);

    void setDebugDrawer(btIDebugDraw* drawer);
    void debugDrawWorld();

    bool raycast(const glm::vec3& origin, const glm::vec3& direction, glm::vec3& hitPoint);

    std::shared_ptr<Box   >  newBox    (glm::vec3 pos, glm::vec3 size  , bool isDynamic);
    std::shared_ptr<Sphere>  newSphere (glm::vec3 pos, float     radius, bool isDynamic);
    std::shared_ptr<Vehicle> newVehicle(glm::vec3 pos);

  private:
    void handleCollision();

    int _physicTicksPerSecond = 30;

    btBroadphaseInterface               * _broadphase            ;
    btDefaultCollisionConfiguration     * _collisionConfiguration;
    btCollisionDispatcher               * _dispatcher            ;
    btSequentialImpulseConstraintSolver * _solver                ;
    btDiscreteDynamicsWorld             * _world                 ;
    btRigidBody                         * _body                  ;
  };
}