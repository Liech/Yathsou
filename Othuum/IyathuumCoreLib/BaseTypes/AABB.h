#pragma once
//Axis Aligned Bounding Box

#include <glm/glm.hpp>
#include <set>

namespace YolonaOss {
  template <size_t Dimension>
  class AABB {
  public:
    using vec = glm::vec<Dimension, float, glm::defaultp>;
    
    AABB() {}
    AABB(vec start, vec size) {
      _position = start;
      _size = size;
    }
    AABB(vec start, float size) {
      _position = start;
      _size = vec(1.0) * size;
    }

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
      _position = pos;
    }

    bool isInside(vec pos) {
      for (size_t i = 0; i < Dimension; i++) {
        if (pos[(int)i] < getPosition()[i] || pos[(int)i] > getPosition()[i] + getSize()[i])
          return false;        
      }
      return true;
    }

    bool intersects(AABB<Dimension> d) {
      throw std::runtime_error("Not yet implemented");
      return true;
    }

    bool intersectsCircle(vec pos, float radius) {
      vec newPos;
      for (size_t i = 0; i < Dimension; i++) {
        newPos[(int)i] = std::clamp(pos[i], _position[(int)i], _position[(int)i] + _size[(int)i]);
      }
      float dist = glm::distance(pos, newPos);
      return dist < radius;
    }

    vec getCenter() {
      return getPosition() + getSize() / 2.0;
    }

  private:
    vec _position;
    vec _size;
  };

}