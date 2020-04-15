#pragma once

#include <memory>
#include "SelenNavigationLib/NavigationMap.h"
#include "IyathuumCoreLib/Tree/Dijkstra.h"
#include "IyathuumCoreLib/BaseTypes/AABB.h"
#include "IyathuumCoreLib/Util/Geometry.h"

namespace Selen {
  template <size_t Dimension>
  class DijkstraMap : public NavigationMap<Dimension> {
    using self = DijkstraMap<Dimension>;
    using vec = std::array<double, Dimension>;
    using Math = Iyathuum::Geometry<Dimension>;
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
        result = Math::normalize(Math::subtract(_target , obj->getPosition()));
      else
        result = Math::normalize(_dijkstra->getDirectionSuggestion(obj->getPosition()));
      if (std::isnan(result[0]))
        return Math::value(0);
      return Math::subtract(Math::multiply(result , obj->getMaxSpeed()) , obj->getVelocity());
    }

  private:
    std::shared_ptr<Iyathuum::DijkstraI<Dimension>> _dijkstra = nullptr;
    vec                                             _target;
  };
}