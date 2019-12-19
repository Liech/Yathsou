#pragma once
//Axis Aligned Bounding Box

#include <glm/glm.hpp>
#include <set>

namespace YolonaOss {
  template <size_t Dimension>
  class AABB {
  public:
    using vec = typedef glm::vec<Dimension, float, glm::defaultp>;
    virtual vec   getPosition() = 0;
    virtual vec   getSize() = 0;

    virtual vec getCenter() {
      return getPosition() + getSize() / 2.0;
    }
  };

  template <size_t Dimension>
  class AABBHierarchyNetwork : public AABB<Dimension>{
    using self = AABBHierarchyNetwork<Dimension>;

    virtual self* getLeaf(vec position)    = 0; //for non hierarchical data just return this
    virtual std::set<self*> getNeighbours() = 0;    
  };
}