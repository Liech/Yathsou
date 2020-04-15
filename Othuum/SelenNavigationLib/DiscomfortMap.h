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
      const float radius = 1;
      auto agents = _agents->findAgents(obj->getPosition(), radius);
      vec result(0.0);
      for (auto agent : agents) {
        if (agent.get() == obj)
          continue;
        vec diff = agent->getPosition() - obj->getPosition();
        float len = glm::length(diff);
        if (len == 0)
          continue;
        float factor = (1.0f - (len / radius));
        //factor *= factor;
        result +=  glm::normalize(diff) * factor;
      }
      //float len = glm::length(result);
      //if (len == 0)
      //  return vec(0.0);
      //result = glm::normalize(result) * obj->getMaxForce() / len;
      return -result;
    }
  private:

  private:
    std::shared_ptr<NavigationAgentManager<Dimension>>     _agents ;
    vec                                                    _target ;
  };
}