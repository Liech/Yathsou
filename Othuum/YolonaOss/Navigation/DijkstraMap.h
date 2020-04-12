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
    
    virtual void setTarget(const vec target) override
    {
      _target = target;
    }

    void setDijkstra(std::shared_ptr<DijkstraI<Dimension>> di) {
      _dijkstra = di;
    }

    virtual vec getDirectionSuggestion(std::shared_ptr<Aura<Dimension>> obj) override {
      vec result;
      if (!_dijkstra)
        result = glm::normalize(_target - obj->getPosition());
      else
        result = glm::normalize(_dijkstra->getDirectionSuggestion(obj->getPosition()));
      if (std::isnan(result[0]))
        return vec(0.0);
      return result;
    }
  private:

  private:
    std::shared_ptr<DijkstraI<Dimension>> _dijkstra = nullptr;
    vec                                   _target;
  };
}