#pragma once

#include <memory>
#include "IyathuumCoreLib/lib/glm/glm.hpp"
#include "SelenNavigationLib/NavigationMap.h"
#include "IyathuumCoreLib/Tree/Dijkstra.h"
#include "IyathuumCoreLib/BaseTypes/glmAABB.h"
#include "IyathuumCoreLib/BaseTypes/MultiDimensionalArray.h"

namespace Selen {
  template <size_t Dimension>
  class GradientGridMap :public NavigationMap<Dimension> {
    using self = GradientGridMap<Dimension>;
    using vec = glm::vec<Dimension, float, glm::defaultp>;
  public:
    GradientGridMap(double scale) {
      _scale = scale;
    }

    virtual void setTarget(const vec target) override
    {
      _target = target;
    }

    void setMap(std::shared_ptr<Iyathuum::MultiDimensionalArray<double,Dimension>> dm) {
      _discomfortMap = dm;
    }

    virtual vec getVelocitySuggestion(NavigationAgent<Dimension>* obj) override {
      if (!_discomfortMap) 
        return vec();
      vec scaled = obj->getPosition() * _scale;
      
      std::array<size_t, Dimension> index;
      for (int i = 0; i < Dimension; i++) {
        size_t t = scaled[i] > 0 ? (size_t)scaled[i] : 0;
        size_t s = _discomfortMap->getDimension(i) - 1;
        index[i] = std::clamp(t, (size_t)0, s);
      }

      vec result = getDirectionSuggestion_recurse(index);
      return result - obj->getVelocity();
    }
  private:
    vec getDirectionSuggestion_recurse(std::array<size_t, Dimension> position, vec dir = vec(), size_t currentDimension = Dimension-1) {
      vec result = vec(0);
      for (int i = -1; i <= 1; i++) {
        auto newP = position;
        if ((!(newP[currentDimension] == 0 && i == -1)) && (!(newP[currentDimension] == _discomfortMap->getDimension(currentDimension)-1 && i==1)))
          newP[currentDimension] += i;          
        dir[(int)currentDimension] = i;
        if (currentDimension != 0)
          result = result + getDirectionSuggestion_recurse(newP,dir, currentDimension - 1);
        else {          
          float val = (float)_discomfortMap->getVal(newP);
          result = result + (dir * -val);
        }        
      }
      return result;
    }

  private:
    std::shared_ptr<Iyathuum::MultiDimensionalArray<double,Dimension>> _discomfortMap = nullptr;
    float                                                              _scale = 1;
    vec                                                                _target;
  };
}