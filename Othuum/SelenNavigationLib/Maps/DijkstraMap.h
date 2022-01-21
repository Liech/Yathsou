#pragma once

#include <memory>
#include "IyathuumCoreLib/lib/glm/glm.hpp"
#include "SelenNavigationLib/Maps/NavigationMap.h"
#include "IyathuumCoreLib/Tree/Dijkstra.h"
#include "IyathuumCoreLib/BaseTypes/glmAABB.h"

namespace Selen {
  template <size_t Dimension>
  class DijkstraMap : public NavigationMap<Dimension> {
    using self = DijkstraMap<Dimension>;
    using vec = glm::vec<Dimension, float, glm::defaultp>;
  public:
    DijkstraMap() {
    }
    
    virtual void setTarget(const vec target) override
    {
      _target = target;
    }

    void setDijkstra(std::shared_ptr<Iyathuum::DijkstraI<Dimension>> di) {
      _dijkstra = di;
    }

    virtual vec getVelocitySuggestion(NavigationAgent<Dimension>* obj) override {
      vec result;
      if (!_dijkstra)
        result = glm::normalize(_target - obj->getPosition());
      else
        result = glm::normalize(_dijkstra->getDirectionSuggestion(obj->getPosition()));
      if (std::isnan(result[0]))
        return vec(0);
      return (result * obj->getMaxSpeed()) - obj->getVelocity();
    }

  private:
    std::shared_ptr<Iyathuum::DijkstraI<Dimension>> _dijkstra = nullptr;
    vec                                             _target;
  };
}