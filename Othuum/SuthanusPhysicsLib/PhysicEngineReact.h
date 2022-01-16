#pragma once

#include <memory>
#include <map>

#include "PhysicEngine.h"

namespace reactphysics3d {
  class PhysicsCommon;
  class PhysicsWorld ;
}

namespace Suthanus {
  class PhysicEngineReact : public PhysicEngine {
  public:
    PhysicEngineReact();
    virtual ~PhysicEngineReact();

    void update()                      override;
    void setTicksPerSecond(int amount) override;

    std::shared_ptr<PhysicObject> raycast(const glm::vec3& origin, const glm::vec3& direction, glm::vec3& hitPoint) const override {
      return {};
    }

    std::vector<std::shared_ptr<PhysicObject>> insideSphere(const glm::vec3& origin, float radius) const { return {}; }
    std::vector<std::shared_ptr<PhysicObject>> insideFrustum(const glm::vec3& origin, const glm::vec3& dirLeftTop, const glm::vec3& dirRightTop, const glm::vec3& dirLeftBot, const glm::vec3& dirRightBot, float nearPlane, float farPlane) const { return {}; }

    std::shared_ptr<Box      > newBox(const glm::vec3& pos, const glm::vec3& size, bool isDynamic) { return nullptr; };
    std::shared_ptr<Sphere   > newSphere(const glm::vec3& pos, float     radius, bool isDynamic);
    std::shared_ptr<HeightMap> newHeightMap(const glm::vec3& pos, const Iyathuum::MultiDimensionalArray<unsigned short, 2>&, float height) { return nullptr; };

    reactphysics3d::PhysicsWorld&  world();
    reactphysics3d::PhysicsCommon& common();
  private:
    int _ticksPerSecond = 10;

    std::map<PhysicObject*, std::weak_ptr<PhysicObject>> _allObjects;

    class pimpl;
    std::unique_ptr<pimpl> _pimpl;
  };
}