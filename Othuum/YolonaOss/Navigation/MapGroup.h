#pragma once

#include "NavigationMap.h"
#include <vector>

namespace YolonaOss {
  template <size_t Dimension>
  class MapGroup : public NavigationMap<Dimension> {
  public:
    virtual void setTarget(const vec target) override
    {
      _target = target; 
      for (size_t i = 0; i < _maps.size(); i++) {
        _maps[i]->setTarget(target);
      }
    }

    virtual vec getDirectionSuggestion(const vec currentPosition) override {
      vec dir(0.0);
      for (size_t i = 0; i < _maps.size(); i++)
        dir += _maps[i]->getDirectionSuggestion(currentPosition) * _influence;
      if (std::isnan(dir[0]))
        return vec();
      return dir;
    }

    void addMap(std::shared_ptr<NavigationMap<Dimension>> map, double influence) {
      _influence.push_back(influence);
      _maps.push_back(map);
    }

  private:
    vec                                                     _target   ;
    std::vector < std::shared_ptr<NavigationMap<Dimension>> _maps     ;
    std::vector < double >                                  _influence;
  };
}