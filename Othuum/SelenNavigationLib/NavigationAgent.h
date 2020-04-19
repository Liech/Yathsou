#pragma once

#include <iostream>
#include <algorithm>

#include "NavigationMap.h"

#include "IyathuumCoreLib/Util/Geometry.h"

#define _USE_MATH_DEFINES
#include <math.h>

namespace Selen {

  template <size_t Dimension>
  class NavigationAgent {
    using vec = std::array<double, Dimension>;
    using Math = Iyathuum::Geometry<Dimension>;

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
      _position = Math::add(_position , _velocity);       
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
      if (Iyathuum::Geometry<Dimension>::length(velocity) == 0)
        return;
      else if (Math::length(velocity) > _maxForce)
        _velocity = Math::add(_velocity,Math::multiply(Math::normalize(velocity) , std::clamp(Math::length(velocity), 0.0, _maxForce)));
      else
        _velocity = Math::add(_velocity,velocity);
      if (Math::length(_velocity) > _maxSpeed)
        _velocity = Math::multiply(Math::normalize(_velocity) , std::clamp(Math::length(_velocity), 0.0, _maxSpeed));
    }

    double                                     _maxSpeed = 0.3                       ;
    double                                     _maxForce = 0.01                      ;

    vec                                       _position                              ;
    vec                                       _target                                ;
    vec                                       _velocity                              ;
    std::shared_ptr<NavigationMap<Dimension>> _map                                   ;
  };
}