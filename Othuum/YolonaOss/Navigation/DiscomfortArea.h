#pragma once

#include "../structs/MultiDimensionalArray.h"
#include "../Util/Geometry.h"
#include "../Util/ImageSubsetUtil.h"
#include <memory>

namespace YolonaOss {
  template<size_t Dimension>
  class DiscomfortArea {
  protected:
    double calcRadius() = 0;
  public:
    double distance2Discomfort(double value) = 0;

    DiscomfortArea(std::shared_ptr<MultiDimensionalArray<double, Dimension>> discomfortField) {
      _discomfortField = discomfortField;
      _radius = calcRadius();
      for (size_t i = 0; i < Dimension; i++) _position[i] = 0;
      for (size_t i = 0; i < Dimension; i++) _futurePosition[i] = 0;
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

    void addDiscomfort(MultiDimensionalArray<double, Dimension>* field, double scale) {
      assert(!_painted);
      _radius = calcRadius();
      double radius = _radius;
      std::array<double, Dimension>       position = _position;
      std::array<double, Dimension> futurePosition = _futurePosition;

      for (size_t i = 0; i < Dimension; i++) {
        position[i] *= scale;
        futurePosition[i] *= scale;
      }

      ImageSubsetUtil::drawCapsule<double, 2>(field, position, futurePosition, radius * scale, [radius, scale](double distance, double val) {return val + distance2Discomfort(distance / scale); });
    }

  private:
    double                        _radius;
    std::array<double, Dimension> _position;
    std::array<double, Dimension> _futurePosition;
  };
}