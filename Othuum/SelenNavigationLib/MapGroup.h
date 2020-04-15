#pragma once

#include "NavigationMap.h"

#include <vector>

#include "IyathuumCoreLib/Util/Geometry.h"

namespace Selen {
  //takes a number of maps and sums the direction suggestion weighted
  template <size_t Dimension>
  class MapGroup : public NavigationMap<Dimension> {
    using Math = Iyathuum::Geometry<Dimension>;
  public:
    using vec = std::array<double, Dimension>;

    virtual void setTarget(const vec target) override
    {
      _target = target; 
      for (size_t i = 0; i < _maps.size(); i++) {
        _maps[i]->setTarget(target);
      }
    }

    virtual vec getVelocitySuggestion(NavigationAgent<Dimension>* obj) override {
      vec dir = Math::value(0);

      for (size_t i = 0; i < _maps.size(); i++) {
        if (_influence[i] > 0)
          dir = Math::add(dir,Math::multiply(_maps[i]->getVelocitySuggestion(obj), _influence[i]));
      }    
      if (std::isnan(dir[0]))
        return vec();
      return dir;
    }

    size_t addMap(std::shared_ptr<NavigationMap<Dimension>> map, float influence) {
      _influence.push_back(influence);
      _maps.push_back(map);
      return _maps.size() - 1;
    }

    void setWeight(size_t mapId, float influence) {
      _influence[mapId] = influence;
    }

  protected:
    vec                                                      _target   ;
    std::vector < std::shared_ptr<NavigationMap<Dimension>>> _maps     ;
    std::vector < float >                                    _influence;
  };
}