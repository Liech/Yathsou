#pragma once

#include <memory>
#include <glm/glm.hpp>
#include "NavigationMap.h"
#include "NavigationAgentManager.h"

namespace Selen {
  template <size_t Dimension>
  class AligmentMap :public NavigationMap<Dimension> {
    using self = AligmentMap<Dimension>;
    using vec = glm::vec<Dimension, float, glm::defaultp>;
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
      vec avg = vec(0);
      if (agents.size() == 1)
        return obj->getVelocity();
      for (auto agent : agents) {
        if (obj == agent.get())
          continue;
        avg = avg + agent->getVelocity();
      }
      avg = avg / (agents.size() - 1);
      return avg - obj->getVelocity();
    }
  private:

  private:
    std::shared_ptr<NavigationAgentManager<Dimension>>     _agents;
    vec                                                    _target;
  };
}