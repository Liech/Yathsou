#pragma once

#include <array>

namespace Iyathuum {
  //Axis Aligned Bounding Box
  template <size_t Dimension>
  class AABB {
  public:
    using vec = std::array<double,Dimension>;
    
    AABB() {
      _position = vec();
      _size = vec();
    }
    AABB(vec start, vec size) {
      _position = start;
      _size = size;
    }
    AABB(vec start, double size) {
      _position = start;
      for (size_t i = 0; i < Dimension; i++)
        _size[i] = size;
    }

    vec getPosition() {
      return _position;
    }

    vec getSize() {
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
        if (pos[i] < getPosition()[i] || pos[i] >= getPosition()[i] + getSize()[i])
          return false;        
      }
      return true;
    }

    bool intersects(AABB<Dimension> d) {
      throw std::runtime_error("Not yet implemented");
      return true;
    }

    bool intersectsCircle(vec pos, double radius) {
      vec newPos;
      for (size_t i = 0; i < Dimension; i++) {
        newPos[i] = std::clamp(pos[i], _position[i], _position[i] + _size[i]);
      }
      double dist = 0; 
      for (size_t i = 0; i < Dimension; i++)
        dist += (pos[i] - newPos[i]) * (pos[i] - newPos[i]);
      dist = std::sqrt(dist);      
      return dist < radius;
    }

    vec getCenter() {
      std::array<double, Dimension> result;
      for (size_t i = 0; i < Dimension; i++)
        result[i] = getPosition()[i] + getSize()[i] / 2.0;
      return result;
    }

    AABB<Dimension> getUnion(AABB<Dimension> other) {

      std::array<double, Dimension> otherPosition  = other.getPosition();
      std::array<double, Dimension> otherSize       = other.getSize();
      std::array<double, Dimension> resultPosition = getPosition();
      std::array<double, Dimension> resultSize     = getSize();

      for (size_t i = 0; i < Dimension; i++) {
        double otherEnd = otherSize[i] + otherPosition[i]  ;
        double end      = resultSize[i] + resultPosition[i];
        if (end < otherEnd)
          resultSize[i] = otherEnd - resultPosition[i];
        if (resultPosition[i] < otherPosition[i]) {
          resultSize[i] -= otherPosition[i] - resultPosition[i];
          resultPosition[i] = otherPosition[i];
        }
        if (resultSize[i] < 0)
          resultSize[i] = 0;
      }
      return AABB<2>(resultPosition, resultSize);
    }

  private:
    vec _position;
    vec _size    ;
  };

}