#pragma once

#include <memory>
#include "IyathuumCoreLib/lib/glm/glm.hpp"
#include "SelenNavigationLib/NavigationMap.h"
#include "IyathuumCoreLib/Tree/Dijkstra.h"
#include "IyathuumCoreLib/BaseTypes/glmAABB.h"
#include "IyathuumCoreLib/BaseTypes/MultiDimensionalArray.h"

namespace Selen {


  /// <summary>
  /// guides the agent away from stuff that is too near, does not pursuit the target
  /// </summary>
  template <size_t Dimension>
  class PersonalSpaceMap : public NavigationMap<Dimension> {
    using self = PersonalSpaceMap<Dimension>;
    using vec = glm::vec<Dimension, float, glm::defaultp>;
  public:
    class PersonalSpaceMapInterface {
    public:
      virtual std::vector<vec> PersonalSpaceQuery(const vec&, float maxDistance) const = 0;
    };


    PersonalSpaceMap(const PersonalSpaceMapInterface& nearQuery) :
    _query(nearQuery){
      
    }

    virtual void setTarget(const vec target) override
    {
    }

    virtual vec getVelocitySuggestion(NavigationAgent<Dimension>* obj) override {
      vec average;
      const float maxDistance = 2;
      vec pos = obj->getPosition();
      std::vector<vec> nearStuff = _query.PersonalSpaceQuery(pos,maxDistance);
      for (auto x : nearStuff) {
        vec diff = x - pos;
        average += diff;
      }
      average /= nearStuff.size();
      return -average;
    }
  private:
    const PersonalSpaceMapInterface& _query;
  };
}