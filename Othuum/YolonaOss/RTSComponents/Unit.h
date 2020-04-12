#pragma once

#include <glm/glm.hpp>
#include "../Navigation/NavigationAgent.h"
#include "Landscape.h"
#include <memory>

namespace YolonaOss{
  template<size_t Dimension>
  class Unit{
    using vec = glm::vec<Dimension, float, glm::defaultp>;
  public:
    Unit(vec position, vec orientation) {
      _navigationAgent = std::make_shared<NavigationAgent<2>>(position, orientation);
    }

    void setTarget(vec target, std::shared_ptr<NavigationMap<Dimension>> map) {
      _navigationAgent->setMap(map);
      _navigationAgent->setTarget(target);
    }

    void setSpeed(float speed) {
      _navigationAgent->setSpeed(speed);
    }

    vec getPosition() {
      return _navigationAgent->getPosition();
    }

    vec getOrientation() {
      return _navigationAgent->getOrientation();
    }

    public:
      std::shared_ptr<NavigationAgent<Dimension>> _navigationAgent;
  };
}