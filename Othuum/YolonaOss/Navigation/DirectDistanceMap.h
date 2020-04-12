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

    virtual vec getDirectionSuggestion(NavigationAgent<Dimension>* obj) override {
      vec dir = glm::normalize(_target - obj->getPosition());
      if (std::isnan(dir[0]))
        return vec();
      return dir;
    }

  private:
    vec _target;
  };
}