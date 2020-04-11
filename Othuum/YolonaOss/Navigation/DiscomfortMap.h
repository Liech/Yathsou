#pragma once

#include <memory>
#include "NavigationMap.h"
#include "AuraHolder.h"
#include "../Util/Util.h"

namespace YolonaOss {
  template <size_t Dimension>
  class DiscomfortMap :public NavigationMap<Dimension> {
    using self = typedef DiscomfortMap<Dimension>;
  public:
    DiscomfortMap(std::shared_ptr<AuraHolder<Dimension>> grid) {
      _grid = grid;
    }

    virtual void setTarget(const vec target) override
    {
      _target = target;
    }

    virtual vec getDirectionSuggestion(const vec currentPosition) override {     
      //_grid->find
      return -vec(0);
    }
  private:

  private:
    std::shared_ptr<AuraHolder<Dimension>>     _grid  ;
    vec                                        _target;
  };
}