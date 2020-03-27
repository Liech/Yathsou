#pragma once
//Axis Aligned Bounding Box

#include <glm/glm.hpp>
#include <set>

namespace YolonaOss {
  template <size_t Dimension>
  class AABB {
  public:
    using vec = typedef glm::vec<Dimension, float, glm::defaultp>;
    
    vec   getPosition() {
      return _position;
    }

    vec   getSize() {
      return _size;
    }

    void setSize(vec size) {
      _size = size;
    }

    void setPosition(vec pos) {
      _position = position;
    }

    bool isInside(vec pos) {
      for (size_t i = 0; i < Dimension; i++) {
        if (pos[i] < getPosition()[i] || pos[i] > getPosition()[i] + getSize()[i])
          return false;        
      }
      return true;
    }

    vec getCenter() {
      return getPosition() + getSize() / 2.0;
    }

  private:
    vec _position;
    vec _size;
  };

}