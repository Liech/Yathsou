#pragma once

#include <memory>
#include <array>

namespace Selen {
  template <size_t Dimension>
  class NavigationAgent;

  template <size_t Dimension>
  class NavigationMap {
  public:
    using vec = std::array<double, Dimension>;
    virtual void setTarget(const vec targetPosition) = 0;
    virtual vec getVelocitySuggestion(NavigationAgent<Dimension>* agent) = 0;
  };
}