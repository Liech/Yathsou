#pragma once

#include "IyathuumCoreLib/lib/glm/glm.hpp"
#include "SelenNavigationLib/NavigationMap.h"
#include "SelenNavigationLib/NavigationAgent.h"

namespace Selen {
  template <size_t Dimension>
  class DirectDistanceMap : public NavigationMap<Dimension> {
    using vec = glm::vec<Dimension, float, glm::defaultp>;
  public:
    virtual void setTarget(const vec target) override
    {
      _target = target; 
    }

    virtual vec getVelocitySuggestion(NavigationAgent<Dimension>* obj) override {
      vec dir = glm::normalize(_target - obj->getPosition());
      float len = glm::distance(_target , obj->getPosition());
      if (len < 0.5f)
        return -obj->getVelocity();
      else if (len < arrivalRadius)
        return (obj->getMaxSpeed() * (len / arrivalRadius)) * dir - obj->getVelocity();
      else
        return obj->getMaxSpeed() * dir- obj->getVelocity();
    }

  private:
    const float arrivalRadius = 3;
    vec _target;
    
  };
}