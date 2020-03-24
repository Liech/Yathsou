#pragma once

#include <glm/glm.hpp>
#include "Navigation/DiscomfortArea.h"
#include "Navigation/NavigationAgent.h"

#include <memory>

namespace YolonaOss{
  template<size_t Dimension>
  class Unit{
    using vec = typedef glm::vec<Dimension, float, glm::defaultp>;
    
    private:
      std::shared_ptr<DiscomfortArea<Dimension>>  _discomfortArea ;
      std::shared_ptr<NavigationAgent<Dimension>> _navigationAgent;
  };
}