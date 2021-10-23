#pragma once

#include <memory>
#include "IyathuumCoreLib/lib/glm/glm.hpp"
#include "SelenNavigationLib/NavigationMap.h"
#include "SelenNavigationLib/NavigationAgentManager.h"

namespace Selen {
  template <size_t Dimension>
  class DiscomfortMap :public NavigationMap<Dimension> {
    using self = DiscomfortMap<Dimension>;
    using vec = glm::vec<Dimension, float, glm::defaultp>;
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
      vec result = vec(0.0);
      for (auto agent : agents) {
        if (agent.get() == obj)
          continue;
        vec diff = agent->getPosition() - obj->getPosition();
        float len = glm::length(diff);
        if (len == 0)
          continue;
        float factor = (1.0f - (len / radius));
        result = result + (glm::normalize(diff) * factor);
      }
      return -result;
    }
  private:

  private:
    std::shared_ptr<NavigationAgentManager<Dimension>>     _agents ;
    vec                                                    _target ;
  };
}