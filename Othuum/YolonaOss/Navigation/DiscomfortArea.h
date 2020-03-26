#pragma once

#include "../structs/MultiDimensionalArray.h"
#include "../Util/Geometry.h"
#include "../Util/ImageSubsetUtil.h"
#include <memory>

namespace YolonaOss {
  template<size_t Dimension>
  class DiscomfortArea {
  public:
    virtual double calcRadius() = 0;
    virtual double distance2Discomfort(double value) = 0;

    DiscomfortArea(double scale) {
      _scale = scale;
      for (size_t i = 0; i < Dimension; i++) _position[i] = 0;
      for (size_t i = 0; i < Dimension; i++) _lastPosition[i] = 0;
    }

    void setPosition(std::array<double, Dimension> position) {
      _position = position;
    }

    void setFuturePosition(std::array<double, Dimension> position) {
      _futurePosition = position;
    }

    double getDiscomfort(std::array<double, Dimension> position) {
      double distance = GeometryND<Dimension>::distancePoint2LineSegment(position, _position, _futurePosition);
      if (distance > _radius) return 0;
      return distance2Discomfort(value);
    }

    void addDiscomfort(MultiDimensionalArray<double, Dimension>* field) {
      assert(!_painted);
      _radius = calcRadius();
      double radius = _radius;
      std::array<double, Dimension>       position = _position;
      //std::array<double, Dimension> futurePosition = _futurePosition;
       
      for (size_t i = 0; i < Dimension; i++) {
        position[i] *= _scale;
        //futurePosition[i] *= scale;
        _lastPosition[i] = _position[i] * _scale;
      }
      //ImageSubsetUtil::drawCapsule<double, 2>(field, position, futurePosition, radius * scale, [radius, scale](double distance, double val) {return val + distance2Discomfort(distance / scale); });
      ImageSubsetUtil::drawCircle<double, 2>(field, position, radius * _scale, [radius, scale](double distance, double val) {return val + distance2Discomfort(distance / scale); });
    }

    bool updateNeeded(){
      if (_radius != getRadius())
        return true;
      for (size_t i = 0; i < Dimension; i++)
        if (_lastPosition[i] != (size_t)(_position[i] * _scale)) return true;
      return false;
    }


  private:
    double                        _radius = 0;
    double                        _scale;
    std::array<size_t, Dimension> _lastPosition;
    std::array<double, Dimension> _position;
  };
}