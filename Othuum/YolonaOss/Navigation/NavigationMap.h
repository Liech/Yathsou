#pragma once

#include <glm/glm.hpp>
#include <memory>

namespace YolonaOss {
  template <size_t Dimension>
  class NavigationAgent;

  template <size_t Dimension>
  class NavigationMap {
  public:
    using vec = glm::vec<Dimension, float, glm::defaultp>;
    virtual void setTarget(const vec targetPosition) = 0;
    virtual vec getDirectionSuggestion(NavigationAgent<Dimension>* agent) = 0;
  };
}