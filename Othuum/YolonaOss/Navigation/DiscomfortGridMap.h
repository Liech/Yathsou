#pragma once

#include <memory>
#include "NavigationMap.h"
#include "../structs/Dijkstra.h"
#include "../structs/AABB.h"
#include "../structs/MultiDimensionalArray.h"

namespace YolonaOss {
  template <size_t Dimension>
  class DiscomfortGridMap :public NavigationMap<Dimension> {
    using self = typedef DiscomfortGridMap<Dimension>;
  public:
    DiscomfortGridMap(double scale) {
      _scale = scale;
    }

    virtual void setTarget(const vec target) override
    {
      _target = target;
    }

    void setMap(std::shared_ptr<MultiDimensionalArray<double,Dimension>> dm) {
      _discomfortMap = dm;
    }

    virtual vec getDirectionSuggestion(const vec currentPosition) override {
      if (!_discomfortMap) 
        return vec();
      vec scaled = _scale * currentPosition;
      
      std::array<size_t, Dimension> index;
      for (int i = 0; i < Dimension; i++)
        index[i] = scaled[i]>0?(size_t)scaled[i]:0;
      return getDirectionSuggestion_recurse(index);
    }
  private:
    vec getDirectionSuggestion_recurse(std::array<size_t, Dimension> position, vec dir = vec(), size_t currentDimension = Dimension-1) {
      vec result = vec(0.0);
      for (int i = -1; i <= 1; i++) {
        auto newP = position;
        if ((!(newP[currentDimension] == 0 && i == -1)) && (!(newP[currentDimension] == _discomfortMap->getDimension(currentDimension)-1 && i==1)))
          newP[currentDimension] += i;          
        dir[currentDimension] = i;
        if (currentDimension != 0)
          result += getDirectionSuggestion_recurse(newP,dir, currentDimension - 1);
        else {          
          float val = _discomfortMap->getVal(newP);
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