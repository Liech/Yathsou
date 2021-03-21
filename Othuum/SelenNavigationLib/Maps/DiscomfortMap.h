#pragma once

#include <memory>
#include "SelenNavigationLib/NavigationMap.h"
#include "SelenNavigationLib/NavigationAgentManager.h"

namespace Selen {
  template <size_t Dimension>
  class DiscomfortMap :public NavigationMap<Dimension> {
    using self = DiscomfortMap<Dimension>;
    using Math = Iyathuum::Geometry<Dimension>;
    using vec = std::array<double, Dimension>;
  public:
    DiscomfortMap(std::shared_ptr<NavigationAgentManager<Dimension>> agents) {
      _agents = agents;
    }

    virtual void setTarget(const vec target) override
    {
      _target = target;
    }

    virtual vec getVelocitySuggestion(NavigationAgent<Dimension>* obj) override {
      const float radius = 1;
      auto agents = _agents->findAgents(obj->getPosition(), radius);
      vec result = Math::value(0.0);
      for (auto agent : agents) {
        if (agent.get() == obj)
          continue;
        vec diff = Math::subtract(agent->getPosition() , obj->getPosition());
        float len = Math::length(diff);
        if (len == 0)
          continue;
        float factor = (1.0f - (len / radius));
        result = Math::add(result, Math::multiply(Math::normalize(diff) , factor));
      }
      return Math::invert(result);
    }
  private:

  private:
    std::shared_ptr<NavigationAgentManager<Dimension>>     _agents ;
    vec                                                    _target ;
  };
}