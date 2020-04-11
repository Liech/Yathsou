#pragma once

#include <memory>
#include "NavigationMap.h"
#include "AuraHolder.h"
#include "../Util/Util.h"

namespace YolonaOss {
  template <size_t Dimension>
  class ComfortMap :public NavigationMap<Dimension> {
    using self = typedef ComfortMap<Dimension>;
  public:
    ComfortMap(std::shared_ptr<AuraHolder<Dimension>> grid) {
      _grid = grid;
    }

    virtual void setTarget(const vec target) override
    {
      _target = target;
    }

    virtual vec getDirectionSuggestion(const vec currentPosition) override {     
      std::array<double, Dimension> pos;
      for (int i = 0; i < Dimension; i++)
        pos[i] = currentPosition[i];

      return vec(0);
    }
  private:

  private:
    std::shared_ptr<AuraHolder<Dimension>> _grid;
    vec                                    _target;
  };
}