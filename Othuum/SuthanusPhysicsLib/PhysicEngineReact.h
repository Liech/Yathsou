#pragma once

#include "PhysicEngine.h"

namespace Suthanus {
  class PhysicEngineReact : public PhysicEngine {
  public:
    PhysicEngineReact();

    void go()                          override {};
    void update()                      override {};
    void setTicksPerSecond(int amount) override {};

    std::shared_ptr<PhysicObject> raycast(const glm::vec3& origin, const glm::vec3& direction, glm::vec3& hitPoint) const override {
      return {};
    }

    std::vector<std::shared_ptr<PhysicObject>> insideSphere(const glm::vec3& origin, float radius) const { return {}; }
    std::vector<std::shared_ptr<PhysicObject>> insideFrustum(const glm::vec3& origin, const glm::vec3& dirLeftTop, const glm::vec3& dirRightTop, const glm::vec3& dirLeftBot, const glm::vec3& dirRightBot, float nearPlane, float farPlane) const { return {}; }

    std::shared_ptr<Box      > newBox(glm::vec3 pos, glm::vec3 size, bool isDynamic) { return nullptr; };
    std::shared_ptr<Sphere   > newSphere(glm::vec3 pos, float     radius, bool isDynamic) { return nullptr; };
    std::shared_ptr<Vehicle  > newVehicle(glm::vec3 pos) { return nullptr; };
    std::shared_ptr<HeightMap> newHeightMap(glm::vec3 pos, const Iyathuum::MultiDimensionalArray<unsigned short, 2>&, float height) { return nullptr; };


  private:

  };
}