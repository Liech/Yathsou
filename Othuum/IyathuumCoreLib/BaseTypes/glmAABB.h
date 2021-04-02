#pragma once

#include "IyathuumCoreLib/lib/glm/glm.hpp"
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

    glmAABB(vec start, vec size) {
      _position = start;
      _size = size;
    }

    glmAABB(vec start, double size) {
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

    void setSize(vec size) {
      _size = size;
    }

    void setPosition(vec pos) {
      _position = pos;
    }

    bool isInside(vec pos) const {
      for (size_t i = 0; i < Dimension; i++) {
        if (pos[i] < getPosition()[i] || pos[i] >= getPosition()[i] + getSize()[i])
          return false;
      }
      return true;
    }

    bool intersects(glmAABB<Dimension> d) const{
      throw std::runtime_error("Not yet implemented");
      return true;
    }

    bool intersectsCircle(vec pos, double radius) const{
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

    glmAABB<Dimension> getIntersection(glmAABB<Dimension> other) const {

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