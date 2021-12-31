#pragma once

#include <array>
#include <set>
#include <memory>
#include <map>

#include "IyathuumCoreLib/lib/glm/vec3.hpp"
#include "IyathuumCoreLib/BaseTypes/MultiDimensionalArray.h"
#include "Objects/Box.h"
#include "Objects/Sphere.h"
#include "Objects/Vehicle.h"
#include "Objects/HeightMap.h"
#include "PhysicEngine.h"

class btBroadphaseInterface;
class btDefaultCollisionConfiguration;
class btCollisionDispatcher;
class btSequentialImpulseConstraintSolver;
class btDiscreteDynamicsWorld;
class btRigidBody;
class btIDebugDraw;
class btCollisionShape;

namespace Suthanus
{
  class PhysicEngineBullet : public PhysicEngine
  {
  public:
    PhysicEngineBullet();
    void go()                          override;
    void update()                      override;
    void setTicksPerSecond(int amount) override;

    void setDebugDrawer(btIDebugDraw* drawer);
    void debugDrawWorld();

    std::shared_ptr<PhysicObject>              raycast(const glm::vec3& origin, const glm::vec3& direction, glm::vec3& hitPoint) const override;
    
    std::vector<std::shared_ptr<PhysicObject>> insideSphere (const glm::vec3& origin, float radius) const override;
    std::vector<std::shared_ptr<PhysicObject>> insideFrustum(const glm::vec3& origin, const glm::vec3& dirLeftTop, const glm::vec3& dirRightTop, const glm::vec3& dirLeftBot, const glm::vec3& dirRightBot, float nearPlane, float farPlane) const override;

    std::shared_ptr<Box      > newBox      (glm::vec3 pos, glm::vec3 size  , bool isDynamic) override;
    std::shared_ptr<Sphere   > newSphere   (glm::vec3 pos, float     radius, bool isDynamic) override;
    std::shared_ptr<Vehicle  > newVehicle  (glm::vec3 pos) override;
    std::shared_ptr<HeightMap> newHeightMap(glm::vec3 pos, const Iyathuum::MultiDimensionalArray<unsigned short, 2>&, float height) override;

  private:
    std::vector<std::shared_ptr<PhysicObject>> insideShape(const glm::vec3& origin, btCollisionShape&) const;

    void handleCollision();

    int _physicTicksPerSecond = 30;

    btBroadphaseInterface               * _broadphase            ;
    btDefaultCollisionConfiguration     * _collisionConfiguration;
    btCollisionDispatcher               * _dispatcher            ;
    btSequentialImpulseConstraintSolver * _solver                ;
    btDiscreteDynamicsWorld             * _world                 ;

    std::map<PhysicObject*, std::weak_ptr<PhysicObject>> _allObjects;
  };
}