#pragma once

#include "../structs/MultiDimensionalArray.h"
#include "../structs/SpatialHash.h"
#include "../Util/Geometry.h"
#include "../Util/ImageSubsetUtil.h"
#include "../Util/Util.h"
#include <memory>

namespace YolonaOss {
  template<size_t Dimension>
  class DiscomfortArea : public ObjectWithAABB<Dimension>{
    using vec = typedef glm::vec<Dimension, float, glm::defaultp>;
  public:
    virtual double calcRadius() = 0;
    virtual double distance2Discomfort(double value) = 0;

    DiscomfortArea(double scale) {
      _scale = scale;
      for (size_t i = 0; i < Dimension; i++) _position[i] = 0;
      for (size_t i = 0; i < Dimension; i++) _lastPosition[i] = 0;
    }

    void setPosition(vec position) {
      _position = position;
    }

    virtual AABB<Dimension> getAABB() override {
      vec start = _position;
      vec size(1.0);
      for (size_t i = 0; i < Dimension; i++) {
        start[i] -= _radius;
        size[i] = _radius * 2;
      }
      AABB<Dimension> result;
      result.setPosition(start);
      result.setSize(size);
      return result; 
    }

    double getDiscomfort(vec position) {
      double distance = glm::distance(position, _position);
      if (distance > _radius) return 0;
      return distance2Discomfort(distance);
    }

    void addDiscomfort(MultiDimensionalArray<double, Dimension>* field) {
      _radius = calcRadius();
      double radius = _radius;
      std::array<double, Dimension>       position;
      //std::array<double, Dimension> futurePosition = _futurePosition;
       
      for (size_t i = 0; i < Dimension; i++) {
        position[i] =  _position[i]* _scale;
        //futurePosition[i] *= scale;
        _lastPosition[i] = _position[i] * _scale;
      }
      //ImageSubsetUtil::drawCapsule<double, 2>(field, position, futurePosition, radius * scale, [radius, scale](double distance, double val) {return val + distance2Discomfort(distance / scale); });
      ImageSubsetUtil::drawCircle<double, 2>(field, position, radius * _scale, [radius,this](double distance, double val) {return val + distance2Discomfort(distance / _scale); });
    }

    bool updateNeeded(){
      if (_radius != getRadius())
        return true;
      for (size_t i = 0; i < Dimension; i++)
        if (_lastPosition[i] != (size_t)(_position[i] * _scale)) return true;
      return false;
    }


  private:
    double                        _radius = 1;
    float                         _scale;
    vec _lastPosition;
    vec _position;
  };
}