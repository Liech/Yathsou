#pragma once

#include "NavigationMap.h"


namespace YolonaOss {
  template <size_t Dimension>
  class DirectDistanceMap : public NavigationMap<Dimension> {
  public:
    virtual void setTarget(const vec target) override
    {
      _target = target; 
    }

    virtual vec getVelocitySuggestion(NavigationAgent<Dimension>* obj) override {
      vec dir = glm::normalize(_target - obj->getPosition());
      float len = glm::length(_target- obj->getPosition());
      if (len < 0.5f)
        return -obj->getVelocity();
      else if (len < arrivalRadius)
        return dir * obj->getMaxSpeed() * (len / arrivalRadius) - obj->getVelocity();
      else
        return dir * obj->getMaxSpeed() - obj->getVelocity();
    }

  private:
    const float arrivalRadius = 3;
    vec _target;
    
  };
}