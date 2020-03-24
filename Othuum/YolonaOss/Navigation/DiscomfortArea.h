#pragma once

#include "structs/MultiDimensionalArray.h"
#include "../Util/Geometry.h"
#include "../Util/ImageSubsetUtil.h"

template<size_t Dimension>
class DiscomfortArea {
public:
  double getRadius() = 0;
  double distance2Discomfort(double value) = 0;

  DiscomfortArea(std::shared_ptr<MultiDimensionalArray<double, Dimension>> discomfortField) {
    _discomfortField = discomfortField;
  }

  void setPosition(std::array<double, Dimension> position) {
    _position = position;
  }

  void setFuturePosition(std::array<double, Dimension> position) {
    _futurePosition = position;
  }

  double getDiscomfort(std::array<double,Dimension> position) {
    double distance = GeometryND<Dimension>::distancePoint2LineSegment(position, _position, _futurePosition);
    if (distance > getRadius()) return 0;
    return distance2Discomfort(value);
  }

  void addDiscomfort(MultiDimensionalArray<double, Dimension>* field) {
    double radius = getRadius();
    ImageSubsetUtil::drawCapsule<double, 2>(field, _position, _futurePosition, radius, [radius](double distance, double val) {return val + distance2Discomfort(val); });
  }

  void removeDiscomfort(MultiDimensionalArray<double, Dimension>* field) {
    double radius = getRadius();
    ImageSubsetUtil::drawCapsule<double, 2>(field, _position, _futurePosition, radius, [radius](double distance, double val) {return val - distance2Discomfort(val); });
  }


private:
  std::array<double, Dimension> _position;
  std::array<double, Dimension> _futurePosition;
};