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
    Unit(Landscape<Dimension>* landscape) {
      _landscape = landscape;
      _navigationAgent = std::make_shared<NavigationAgent<2>>(glm::vec2(3, 3));
      _navigationAgent->setMap(_landscape->getMap(vec(0.0)));

    }

    void setTarget(vec target) {
      _navigationAgent->setMap(_landscape->getMap(target));
      _navigationAgent->setTarget(target);
    }

    public:
      std::shared_ptr<DiscomfortArea<Dimension>>  _discomfortArea ;
      std::shared_ptr<NavigationAgent<Dimension>> _navigationAgent;
      Landscape<Dimension>*                       _landscape;
  };
}