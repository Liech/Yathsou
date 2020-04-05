#pragma once

#include <glm/glm.hpp>
#include <iostream>
#include "NavigationMap.h"

#define _USE_MATH_DEFINES
#include <math.h>

namespace YolonaOss {

  template <size_t Dimension>
  class NavigationAgent {
    using vec = typedef glm::vec<Dimension, float, glm::defaultp>;

  public:
    NavigationAgent(vec pos, vec orientation) {      
      _position = pos;
      _orientation = orientation;
      _target = pos;
      _map = nullptr;
    }

    void updatePosition() {
      if (_map == nullptr)
        return;
      vec dir = _map->getDirectionSuggestion(_position);
      float dist = glm::distance(_target, _position);
      if (dist < 0.01f || glm::length(dir) < 0.01)
        return;
      dir = glm::normalize(dir);
      _orientation = GeometryND<Dimension>::slerp(_orientation, dir, 0.2f);
      vec movement = _orientation * _speed;
      if (glm::length(movement) > dist)
        movement = glm::normalize(movement) * dist * 0.5f;
      _position = _position + movement;       
    }

    void setMap(std::shared_ptr<NavigationMap<Dimension>> map) {
      _map = map;
    }

    void setTarget(vec position) {
      _target = position;
    }

    void setPosition(vec position) {
      _position = position;
    }

    vec getPosition() {
      return _position;
    }

    vec getOrientation() {
      return _orientation;
    }

    void setOrientation(vec orientation) {
      _orientation = orientation;
    }

    void setSpeed(float speed) {
      _speed = speed;
    }

  private:   
    float                                     _speed = 0.1f               ;
    float                                     _turnSpeed = M_PI * 2 / 10.0;

    vec                                       _position                   ;
    vec                                       _target                     ;
    vec                                       _orientation                ;
    std::shared_ptr<NavigationMap<Dimension>> _map                        ;
  };
}