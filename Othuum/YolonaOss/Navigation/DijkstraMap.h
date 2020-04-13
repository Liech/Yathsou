#pragma once

#include <memory>
#include "NavigationMap.h"
#include "IyathuumCoreLib/Tree/Dijkstra.h"
#include "IyathuumCoreLib/BaseTypes/AABB.h"

namespace YolonaOss {
  template <size_t Dimension>
  class DijkstraMap :public NavigationMap<Dimension> {
    using self = DijkstraMap<Dimension>;
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
        result = glm::normalize(Util<2>::array2Vec<double>(_dijkstra->getDirectionSuggestion(Util<2>::vec2Array<double>(obj->getPosition()))));
      if (std::isnan(result[0]))
        return vec(0.0);
      return result * obj->getMaxSpeed() - obj->getVelocity();
    }
  private:

  private:
    std::shared_ptr<Iyathuum::DijkstraI<Dimension>> _dijkstra = nullptr;
    vec                                             _target;
  };
}