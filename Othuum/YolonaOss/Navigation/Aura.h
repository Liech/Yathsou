#pragma once

#include "../structs/MultiDimensionalArray.h"
#include "../structs/SpatialHash.h"
#include "../Util/Geometry.h"
#include "../Util/ImageSubsetUtil.h"
#include "../Util/Util.h"
#include <memory>

namespace YolonaOss {
  //An Aura is an area that is notified by other units. Friendly auras invite to grouping. The Auras of foes might be feared  
  template<size_t Dimension>
  class Aura {
    using vec = typedef glm::vec<Dimension, float, glm::defaultp>;
  public:

    Aura(double scale) {
      _scale = scale;
      for (size_t i = 0; i < Dimension; i++) _position[i] = 0;
    }

    vec getPosition() {
      return _position;
    }

    void setPosition(vec position) {
      _position = position;
    }

    void setRadius(float radius) {
      _radius = radius;
    }

    double getDistance(vec position) {
      double distance = glm::distance(position, _position) - _radius;
      if (distance < 0) return 0;
      return distance;
    }

  private:
    double                        _radius = 0.5f;
    float                         _scale        ;
    vec                           _position     ;
  };
}