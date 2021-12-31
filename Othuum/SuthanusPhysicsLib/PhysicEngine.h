#pragma once

#include <memory>
#include <vector>
#include "IyathuumCoreLib/lib/glm/glm.hpp"
#include "IyathuumCoreLib/BaseTypes/MultiDimensionalArray.h"

namespace Suthanus {
  class PhysicObject;
  class Box;
  class Sphere;
  class Vehicle;
  class HeightMap;

  class PhysicEngine {
  public:
    virtual void go()                          = 0;
    virtual void update()                      = 0;
    virtual void setTicksPerSecond(int amount) = 0;

    virtual std::shared_ptr<PhysicObject> raycast(const glm::vec3& origin, const glm::vec3& direction, glm::vec3& hitPoint) const = 0;

    virtual std::vector<std::shared_ptr<PhysicObject>> insideSphere(const glm::vec3& origin, float radius) const                                                                                                                                           = 0;
    virtual std::vector<std::shared_ptr<PhysicObject>> insideFrustum(const glm::vec3& origin, const glm::vec3& dirLeftTop, const glm::vec3& dirRightTop, const glm::vec3& dirLeftBot, const glm::vec3& dirRightBot, float nearPlane, float farPlane) const = 0;

    virtual std::shared_ptr<Box      > newBox(glm::vec3 pos, glm::vec3 size, bool isDynamic)                                                = 0;
    virtual std::shared_ptr<Sphere   > newSphere(glm::vec3 pos, float     radius, bool isDynamic)                                           = 0;
    virtual std::shared_ptr<Vehicle  > newVehicle(glm::vec3 pos)                                                                            = 0;
    virtual std::shared_ptr<HeightMap> newHeightMap(glm::vec3 pos, const Iyathuum::MultiDimensionalArray<unsigned short, 2>&, float height) = 0;
  };
}