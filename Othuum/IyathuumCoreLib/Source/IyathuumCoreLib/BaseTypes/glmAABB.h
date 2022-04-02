#pragma once

#include <glm/glm.hpp>
#include <stdexcept>
#include <algorithm>

namespace Iyathuum {
  template<size_t Dimension>
  class glmAABB {
    using vec = glm::vec<Dimension, float, glm::defaultp>;
  public:
    glmAABB() {
      _position = vec();
      _size = vec();
    }

    glmAABB(const vec& start, const vec& size) {
      _position = start;
      _size = size;
    }

    glmAABB(const vec& start, double size) {
      _position = start;
      for (size_t i = 0; i < Dimension; i++)
        _size[i] = size;
    }

    vec getPosition() const {
      return _position;
    }

    vec getSize() const {
      return _size;
    }

    void setSize(const vec& size) {
      _size = size;
    }

    void setPosition(const vec& pos) {
      _position = pos;
    }

    void setCenter(const vec& pos) {
      _position = pos - _size / 2.0f;
    }

    bool isInside(const vec& pos) const {
      for (size_t i = 0; i < Dimension; i++) {
        if (pos[i] < getPosition()[i] || pos[i] >= getPosition()[i] + getSize()[i])
          return false;
      }
      return true;
    }

    bool intersects(const glmAABB<Dimension>& d) const{
      if (d.getPosition()[0] + d.getSize()[0] < getPosition()[0]) return false;
      if (d.getPosition()[1] + d.getSize()[1] < getPosition()[1]) return false;
      if (d.getPosition()[0] > getPosition()[0] + getSize()[0]) return false;
      if (d.getPosition()[1] > getPosition()[1] + getSize()[1]) return false;
      return true;
    }

    bool intersectsSphere(vec pos, double radius) const{
      //nearest point of box to sphere center
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

    vec getCenter() const{
      vec result;
      for (size_t i = 0; i < Dimension; i++)
        result[i] = getPosition()[i] + getSize()[i] / 2.0;
      return result;
    }

    glmAABB<Dimension> getIntersection(const glmAABB<Dimension>& other) const {

      vec otherPosition  = other.getPosition();
      vec otherSize      = other.getSize();
      vec resultPosition = getPosition();
      vec resultSize     = getSize();

      for (size_t i = 0; i < Dimension; i++) {
        if (otherPosition[i] + otherSize[i] < resultPosition[i] + resultSize[i])
          resultSize[i] = (otherPosition[i] + otherSize[i]) - resultPosition[i];
        else
          resultSize[i] = (resultPosition[i] + resultSize[i]) - otherPosition[i];
        if (otherPosition[i] > resultPosition[i]) {
          resultSize[i] = resultSize[i] - (otherPosition[i] - resultPosition[i]);
          resultPosition[i] = otherPosition[i];
        }
        if (resultSize[i] < 0)
          resultSize[i] = 0;
      }
      return glmAABB<2>(resultPosition, resultSize);
    }

  private:
    vec _position;
    vec _size;
  };
}