#pragma once

#include "../structs/MultiDimensionalArray.h"
#include "../Util/Geometry.h"
#include "../Util/ImageSubsetUtil.h"
#include <memory>

namespace YolonaOss {
  template<size_t Dimension>
  class LinearDiscomfort : public DiscomfortArea<Dimension>{
  public:
    virtual double calcRadius() override {
      return _rad;
    };
    virtual double distance2Discomfort(double value) override {
      if (value > _rad) 
        return 0;
      return (_rad-value) / _rad;
    }

    LinearDiscomfort(double radius, double scale) : DiscomfortArea(scale) {
      _rad = radius;
    }
  private:
    double _rad = 0;
  };
}