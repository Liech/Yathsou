#pragma once

#include <memory>
#include "SelenNavigationLib/NavigationMap.h"
#include "SelenNavigationLib/NavigationAgentManager.h"

namespace Selen {
  template <size_t Dimension>
  class AligmentMap :public NavigationMap<Dimension> {
    using self = DiscomfortMap<Dimension>;
    using Math = Iyathuum::Geometry<Dimension>;
    using vec = std::array<double, Dimension>;
  public:
    AligmentMap(std::shared_ptr<NavigationAgentManager<Dimension>> agents) {
      _agents = agents;
    }

    virtual void setTarget(const vec target) override
    {
      _target = target;
    }

    virtual vec getVelocitySuggestion(NavigationAgent<Dimension>* obj) override {
      float radius = 2;
      auto agents = _agents->findAgents(obj->getPosition(), radius);
      vec avg = Math::value(0);
      if (agents.size() == 1)
        return obj->getVelocity();
      for (auto agent : agents) {
        if (obj == agent.get())
          continue;
        avg = Math::add(avg,agent->getVelocity());
      }
      avg = Math::divide(avg , agents.size() - 1);
      return Math::subtract(avg , obj->getVelocity());
    }
  private:

  private:
    std::shared_ptr<NavigationAgentManager<Dimension>>     _agents;
    vec                                                    _target;
  };
}