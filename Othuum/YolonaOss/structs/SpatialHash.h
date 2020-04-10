#pragma once

#include <memory>
#include "AABB.h"

namespace YolonaOss {
  
  template<size_t Dimension>
  class ObjectWithAABB {
  public:
    virtual AABB<Dimension> getAABB() = 0;
  };

  template<size_t Dimension>
  class SpatialHash : public ObjectWithAABB <Dimension>{
    using vec = typedef glm::vec<Dimension, float, glm::defaultp>;
  public:
    virtual void updateObject(std::shared_ptr<ObjectWithAABB<Dimension>> object) = 0;
    virtual void addObject   (std::shared_ptr<ObjectWithAABB<Dimension>> object) = 0;
    virtual void removeObject(std::shared_ptr<ObjectWithAABB<Dimension>> object) = 0;

    virtual std::set<std::shared_ptr<ObjectWithAABB<Dimension>>> findObjects(vec  position) = 0;
    virtual std::set<std::shared_ptr<ObjectWithAABB<Dimension>>> findObjects(AABB<Dimension> position) = 0;
  };
}