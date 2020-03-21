#pragma once

#include <glm/glm.hpp>
#include <iostream>
#include "NavigationMap.h"

namespace YolonaOss {

  template <size_t Dimension>
  class NavigationAgent {
    using vec = typedef glm::vec<Dimension, float, glm::defaultp>;

  public:
    NavigationAgent(vec pos) {      
      _position = pos;
      _target = pos;
      _map = nullptr;
    }

    void updatePosition() {
      if (_map == nullptr)
        throw std::runtime_error("No Map Assigned");
      vec dir = _map->getDirectionSuggestion(_position, _target);
      float dist = glm::distance(_target, _position);
      if (dist < 0.01f)
        return;
      _position = _position + dir * 0.005f /** dist*/;       
    }

    void setMap(std::shared_ptr<NavigationMap<Dimension>> map) {
      _map = map;
    }

    void setTarget(vec position) {
      _target = position;
    }

    vec getPosition() {
      return _position;
    }

  private:   
    vec                            _position;
    vec                            _target;
    std::shared_ptr<NavigationMap<Dimension>> _map;
  };
}