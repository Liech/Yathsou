#pragma once

#include "NavigationMap.h"


namespace YolonaOss {
  template <size_t Dimension>
  class DirectDistanceMap :public NavigationMap<Dimension> {
  public:
    virtual vec getDirectionSuggestion(const vec currentPosition, const vec target) override {
      vec dir = glm::normalize(target - currentPosition);
      if (std::isnan(dir[0]))
        return vec();
      return dir;
    }
  };
}