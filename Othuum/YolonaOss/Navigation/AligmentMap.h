#pragma once

#include <memory>
#include "NavigationMap.h"
#include "NavigationAgentManager.h"
#include "../Util/Util.h"

namespace YolonaOss {
  template <size_t Dimension>
  class AligmentMap :public NavigationMap<Dimension> {
    using self = DiscomfortMap<Dimension>;
  public:
    AligmentMap(std::shared_ptr<NavigationAgentManager<Dimension>> agents) {
      _agents = agents;
    }

    virtual void setTarget(const vec target) override
    {
      _target = target;
    }

    virtual vec getDirectionSuggestion(NavigationAgent<Dimension>* obj) override {
      auto agents = _agents->findAgents(obj->getPosition(), 2);
      vec avg(0.0);
      if (agents.size() == 1)
        return obj->getVelocity();
      for (auto agent : agents) {
        if (obj == agent.get())
          continue;
        avg += agent->getVelocity();
      }
      avg /= agents.size() - 1;
      return avg;
    }
  private:

  private:
    std::shared_ptr<NavigationAgentManager<Dimension>>     _agents;
    vec                                                    _target;
  };
}