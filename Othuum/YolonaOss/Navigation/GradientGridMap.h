#pragma once

#include <memory>
#include "NavigationMap.h"
#include "../structs/Dijkstra.h"
#include "../structs/AABB.h"
#include "../structs/MultiDimensionalArray.h"

namespace YolonaOss {
  template <size_t Dimension>
  class GradientGridMap :public NavigationMap<Dimension> {
    using self = GradientGridMap<Dimension>;
  public:
    GradientGridMap(double scale) {
      _scale = scale;
    }

    virtual void setTarget(const vec target) override
    {
      _target = target;
    }

    void setMap(std::shared_ptr<MultiDimensionalArray<double,Dimension>> dm) {
      _discomfortMap = dm;
    }

    virtual vec getVelocitySuggestion(NavigationAgent<Dimension>* obj) override {
      if (!_discomfortMap) 
        return vec();
      vec scaled = _scale * obj->getPosition();
      
      std::array<size_t, Dimension> index;
      for (int i = 0; i < Dimension; i++) {
        size_t t = scaled[i] > 0 ? (size_t)scaled[i] : 0;
        size_t s = _discomfortMap->getDimension(i) - 1;
        index[i] = std::clamp(t, (size_t)0, s);
      }

      vec result = glm::normalize(getDirectionSuggestion_recurse(index));
      if (std::isnan(result[0]))
        return vec(0.0);
      return result;
    }
  private:
    vec getDirectionSuggestion_recurse(std::array<size_t, Dimension> position, vec dir = vec(), size_t currentDimension = Dimension-1) {
      vec result = vec(0.0);
      for (int i = -1; i <= 1; i++) {
        auto newP = position;
        if ((!(newP[currentDimension] == 0 && i == -1)) && (!(newP[currentDimension] == _discomfortMap->getDimension(currentDimension)-1 && i==1)))
          newP[currentDimension] += i;          
        dir[(int)currentDimension] = i;
        if (currentDimension != 0)
          result += getDirectionSuggestion_recurse(newP,dir, currentDimension - 1);
        else {          
          float val = (float)_discomfortMap->getVal(newP);
          result += dir * -val;
        }        
      }
      return result;
    }

  private:
    std::shared_ptr<MultiDimensionalArray<double,Dimension>> _discomfortMap = nullptr;
    float                                                   _scale = 1;
    vec                                                      _target;
  };
}