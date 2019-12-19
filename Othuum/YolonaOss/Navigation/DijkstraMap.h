#pragma once

#include <memory>
#include "NavigationMap.h"
#include "../structs/Dijkstra.h"
#include "../structs/AABB.h"

namespace YolonaOss {
  template <size_t Dimension>
  class DijkstraMap :public NavigationMap<Dimension> {
    using self = typedef DijkstraMap<Dimension>;
  public:
    DijkstraMap(vec start, std::shared_ptr<AABBHierarchyNetwork<Dimension>> root) {
      _dijkstra = new std::shared_ptr<AABBDijkstra<Dimension>>(start, root, self::getWeight);
    }

    virtual vec getDirectionSuggestion(const vec currentPosition, const vec target) override {
      vec dir = glm::normalize(target - currentPosition);
      if (std::isnan(dir[0]))
        return vec();
      return dir;
    }
  private:
    static double getWeight(AABBHierarchyNetwork<Dimension>* node) {
      return 1;
    }

  private:
    std::shared_ptr<AABBDijkstra<Dimension>> _dijkstra;
  };
}