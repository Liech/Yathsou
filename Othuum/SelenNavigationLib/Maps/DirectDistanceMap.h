#pragma once

#include "SelenNavigationLib/NavigationMap.h"
#include "SelenNavigationLib/NavigationAgent.h"
#include "IyathuumCoreLib/Util/Geometry.h"

namespace Selen {
  template <size_t Dimension>
  class DirectDistanceMap : public NavigationMap<Dimension> {
    using vec = std::array<double, Dimension>;
    using Math = Iyathuum::Geometry<Dimension>;
  public:
    virtual void setTarget(const vec target) override
    {
      _target = target; 
    }

    virtual vec getVelocitySuggestion(NavigationAgent<Dimension>* obj) override {
      vec dir = Math::normalize(Math::subtract(_target , obj->getPosition()));
      float len = Math::length(Math::subtract(_target , obj->getPosition()));
      if (len < 0.5f)
        return Math::invert(obj->getVelocity());
      else if (len < arrivalRadius)
        return Math::subtract(Math::multiply(dir , obj->getMaxSpeed() * (len / arrivalRadius)) , obj->getVelocity());
      else
        return Math::subtract(Math::multiply(dir , obj->getMaxSpeed()), obj->getVelocity());
    }

  private:
    const float arrivalRadius = 3;
    vec _target;
    
  };
}