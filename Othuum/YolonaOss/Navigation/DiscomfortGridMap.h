#pragma once

#include <memory>
#include "NavigationMap.h"
#include "DiscomfortGrid.h"
#include "../Util/Util.h"

namespace YolonaOss {
  template <size_t Dimension>
  class DiscomfortGridMap :public NavigationMap<Dimension> {
    using self = typedef DiscomfortGridMap<Dimension>;
  public:
    DiscomfortGridMap(std::shared_ptr<DiscomfortGrid<Dimension>> grid) {
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

      return -_grid->getGradient(currentPosition);
    }
  private:

  private:
    std::shared_ptr<DiscomfortGrid<Dimension>> _grid;
    vec                                        _target;
  };
}