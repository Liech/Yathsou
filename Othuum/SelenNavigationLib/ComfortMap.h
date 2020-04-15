#pragma once

#include <memory>
#include "NavigationMap.h"
#include "NavigationAgentManager.h"
#include "../Util/Util.h"

namespace YolonaOss {
  template <size_t Dimension>
  class ComfortMap :public NavigationMap<Dimension> {
    using self = ComfortMap<Dimension>;
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
      vec avg(0.0);
      for (auto agent : agents) {
        if (obj == agent.get())
          continue;
        avg += agent->getPosition();
      }
      if (agents.size() == 1)
        return vec(0.0);
      avg /= (float)agents.size()-1;
      vec result = avg - obj->getPosition();
      float len = glm::length(result);
      if (len > obj->getMaxForce())
        result = glm::normalize(result) * obj->getMaxForce() / len;
      if (len == 0)
        return vec(0.0);


      return result - obj->getVelocity();
    }

  private:

  private:
    std::shared_ptr<NavigationAgentManager<Dimension>> _agents ;
    vec                                                _target ;
  };
}