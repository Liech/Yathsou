#pragma once

#include <glm/glm.hpp>
#include <iostream>
#include "NavigationMap.h"

#define _USE_MATH_DEFINES
#include <math.h>

namespace YolonaOss {

  template <size_t Dimension>
  class NavigationAgent {
    using vec = glm::vec<Dimension, float, glm::defaultp>;

  public:
    NavigationAgent(vec pos, vec velocity) {      
      _position    = pos        ;
      _velocity    = velocity   ;
      _target      = pos        ;
      _map         = nullptr    ;
    }

    void updatePosition() {
      if (_map == nullptr)
        return;
      vec dir = _map->getVelocitySuggestion(this);
      applyForce(dir);
      _position = _position + _velocity;       
    }

    void setMap(std::shared_ptr<NavigationMap<Dimension>> map) {
      _map = map;
    }
    
    std::shared_ptr<NavigationMap<Dimension>> getMap() {
      return _map;
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

    vec getVelocity() {
      return _velocity;
    }

    void setSpeed(float speed) {
      _maxSpeed = speed;
    }

    void setForce(float speed) {
      _maxForce = speed;
    }

    float getMaxSpeed() {
      return _maxSpeed;
    }

    float getMaxForce() {
      return _maxForce;
    }

  private:   
    void applyForce(vec velocity) {
      if (glm::length(velocity) == 0)
        return;
      else if (glm::length(velocity) > _maxForce)
        _velocity += glm::normalize(velocity) * std::clamp(glm::length(velocity), 0.0f, _maxForce);
      else
        _velocity += velocity;
      if (glm::length(_velocity) > _maxSpeed)
        _velocity = glm::normalize(_velocity) * std::clamp(glm::length(_velocity), 0.0f, _maxSpeed);
    }

    float                                     _maxSpeed = 0.3f                       ;
    float                                     _maxForce = 0.01f                      ;

    vec                                       _position                              ;
    vec                                       _target                                ;
    vec                                       _velocity                              ;
    std::shared_ptr<NavigationMap<Dimension>> _map                                   ;
  };
}