#pragma once

#include <memory>
#include "NavigationMap.h"
#include "NavigationAgentManager.h"
#include "../Util/Util.h"

namespace YolonaOss {
  template <size_t Dimension>
  class DiscomfortMap :public NavigationMap<Dimension> {
    using self = DiscomfortMap<Dimension>;
  public:
    DiscomfortMap(std::shared_ptr<NavigationAgentManager<Dimension>> agents) {
      _agents = agents;
    }

    virtual void setTarget(const vec target) override
    {
      _target = target;
    }

    virtual vec getVelocitySuggestion(NavigationAgent<Dimension>* obj) override {
      const float radius = 4;
      auto agents = _agents->findAgents(obj->getPosition(), radius);
      vec result(0.0);
      for (auto agent : agents) {
        if (agent.get() == obj)
          continue;
        result += agent->getPosition() - obj->getPosition();
      }
      result /= agents.size()-1;
      result /= radius;
      
      float len = 1.0f - glm::length(result);
      len *= len;
      if (std::isnan(glm::normalize(result)[0]))
        return vec(0.0);
      result = glm::normalize(result) * len;
      
      return -result*2.0f;
    }
  private:

  private:
    std::shared_ptr<NavigationAgentManager<Dimension>>     _agents ;
    vec                                                    _target ;
  };
}