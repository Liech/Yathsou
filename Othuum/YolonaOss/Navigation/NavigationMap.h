#pragma once

#include <glm/glm.hpp>
  
namespace YolonaOss {
  template <size_t Dimension>
  class NavigationMap {
  public:
    using vec = typedef glm::vec<Dimension, float, glm::defaultp>;
    virtual vec getDirectionSuggestion(const vec currentPosition, const vec target) = 0;
  };
}