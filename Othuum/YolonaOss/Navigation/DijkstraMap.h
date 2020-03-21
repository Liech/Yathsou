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
    DijkstraMap() {
    }

    void setDijkstra(std::shared_ptr<DijkstraI<Dimension>> di) {
      _dijkstra = di;
    }

    virtual vec getDirectionSuggestion(const vec currentPosition, const vec target) override {
      if (!_dijkstra) return glm::normalize(target - currentPosition);
      return _dijkstra->getDirectionSuggestion(currentPosition);
    }
  private:

  private:
    std::shared_ptr<DijkstraI<Dimension>> _dijkstra = nullptr;
  };
}