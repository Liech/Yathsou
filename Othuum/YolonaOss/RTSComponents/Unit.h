#pragma once

#include <glm/glm.hpp>
#include "../Navigation/DiscomfortArea.h"
#include "../Navigation/NavigationAgent.h"
#include "Landscape.h"
#include <memory>

namespace YolonaOss{
  template<size_t Dimension>
  class Unit{
    using vec = typedef glm::vec<Dimension, float, glm::defaultp>;
  public:
    Unit(vec v) {
      _navigationAgent = std::make_shared<NavigationAgent<2>>(v);

    }

    void setTarget(vec target, std::shared_ptr<NavigationMap<Dimension>> map) {
      _navigationAgent->setMap(map);
      _navigationAgent->setTarget(target);
    }

    vec getPosition() {
      return _navigationAgent->getPosition();
    }

    public:
      std::shared_ptr<DiscomfortArea<Dimension>>  _discomfortArea ;
      std::shared_ptr<NavigationAgent<Dimension>> _navigationAgent;
  };
}