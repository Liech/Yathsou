#pragma once

#include <memory>
#include <IyathuumCoreLib/lib/glm/glm.hpp>

#include "Landscape.h"

#include "SelenNavigationLib/NavigationAgent.h"

namespace YolonaOss{
  template<size_t Dimension>
  class Unit{
    using vec  = glm::vec<Dimension, float, glm::defaultp>;
    using Math = Iyathuum::Geometry<Dimension>;
  public:
    Unit(vec position, vec orientation) {
      _navigationAgent = std::make_shared<Selen::NavigationAgent<2>>(Util<Dimension>::vec2Array<double>(position), Util<Dimension>::vec2Array<double>(orientation));
    }

    void setTarget(vec target, std::shared_ptr<Selen::NavigationMap<Dimension>> map) {
      _navigationAgent->setMap(map);
      _navigationAgent->setTarget(Util<Dimension>::vec2Array<double>(target));
    }

    void setSpeed(float speed) {
      _navigationAgent->setSpeed(speed);
    }

    vec getPosition() {
      return Util<Dimension>::array2Vec<double>(_navigationAgent->getPosition());
    }

    vec getOrientation() {
      if (Math::length(_navigationAgent->getVelocity())< 1e-5)
        return lastVelocity;
      lastVelocity = glm::normalize(Util<Dimension>::array2Vec<double>(_navigationAgent->getVelocity()));
      return lastVelocity;
    }

    public:
      std::shared_ptr<Selen::NavigationAgent<Dimension>> _navigationAgent;
      vec lastVelocity = glm::normalize(vec(1.0));
  };
}