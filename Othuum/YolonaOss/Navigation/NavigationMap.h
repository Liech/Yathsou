#pragma once

#include <glm/glm.hpp>
#include "Aura.h"
  
namespace YolonaOss {
  template <size_t Dimension>
  class NavigationMap {
  public:
    using vec = typedef glm::vec<Dimension, float, glm::defaultp>;
    virtual void setTarget(const vec targetPosition) = 0;
    virtual vec getDirectionSuggestion(std::shared_ptr<Aura<Dimension>>) = 0;    
  };
}