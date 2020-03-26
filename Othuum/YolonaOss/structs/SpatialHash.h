#pragma once

#include "MultiDimensionalArray.h"
#include "AABB.h"

namespace YolonaOss {
  
  template<size_t Dimension>
  class ObjectWithAABB {
  public:
    virtual AABB getAABB() = 0;
  };

  template<size_t Dimension>
  class SpatialHash : public ObjectWithAABB{
    using vec = typedef glm::vec<Dimension, float, glm::defaultp>;
  public:
    virtual void updateObject(std::shared_ptr<ObjectWithAABB<Dimension>> object) = 0;
    virtual void addObject   (std::shared_ptr<ObjectWithAABB<Dimension>> object) = 0;
    virtual void removeObject(std::shared_ptr<ObjectWithAABB<Dimension>> object) = 0;

    virtual std::set<std::shared_ptr<ObjectWithAABB<Dimension>>> findObjects(vec  position) = 0;
    virtual std::set<std::shared_ptr<ObjectWithAABB<Dimension>>> findObjects(AABB position) = 0;
  };
}