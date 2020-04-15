#pragma once

#include <memory>
#include "SelenNavigationLib/NavigationMap.h"
#include "SelenNavigationLib/NavigationAgentManager.h"

namespace Selen {
  template <size_t Dimension>
  class ComfortMap :public NavigationMap<Dimension> {
    using self = ComfortMap<Dimension>;
    using Math = Iyathuum::Geometry<Dimension>;
  public:
    ComfortMap(std::shared_ptr<NavigationAgentManager<Dimension>> agents) {
      _agents = agents;
    }

    virtual void setTarget(const vec target) override
    {
      _target = target;
    }

    virtual vec getVelocitySuggestion(NavigationAgent<Dimension>* obj) override {
      float radius = 4;
      auto agents = _agents->findAgents(obj->getPosition(), radius);
      vec avg = Math::value(0);
      for (auto agent : agents) {
        if (obj == agent.get())
          continue;
        avg = Math::add(avg,agent->getPosition());
      }
      if (agents.size() == 1)
        return Math::value(0);
      avg = Math::divide(avg, (float)agents.size()-1);
      vec result = Math::subtract(avg , obj->getPosition());
      float len = Math::length(result);
      if (len > obj->getMaxForce())
        result = Math::multiply(Math::normalize(result) , obj->getMaxForce() / len);
      if (len == 0)
        return Math::value(0);


      return Math::subtract(result , obj->getVelocity());
    }

  private:

  private:
    std::shared_ptr<NavigationAgentManager<Dimension>> _agents ;
    vec                                                _target ;
  };
}