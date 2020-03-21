#pragma once

#include <glm/glm.hpp>
  
namespace YolonaOss {
  template <size_t Dimension>
  class NavigationMap {
  public:
    using vec = typedef glm::vec<Dimension, float, glm::defaultp>;
    virtual void setTarget(const vec targetPosition) = 0;
    virtual vec getDirectionSuggestion(const vec currentPosition) = 0;    
  };
}