#pragma once

#include "../structs/MultiDimensionalArray.h"
#include "DiscomfortArea.h"
#include <set>
#include "../Util/Geometry.h"
#include "../Util/Util.h"
#include "../structs/GridHash.h"

namespace YolonaOss {
  template<size_t Dimension>
  class DiscomfortGrid {
    using vec = typedef glm::vec<Dimension, float, glm::defaultp>;
  public:
    DiscomfortGrid(std::array<size_t, Dimension> dimension, double scale){
      _scale = scale;

      std::array<size_t, Dimension> min;
      std::array<size_t, Dimension> size;
      for (size_t i = 0; i < Dimension; i++) {
        min[i] = 0;
        size[i] = 3;
      }
      vec one;
      for (size_t i = 0; i < Dimension; i++)one[i] = 1;
      for (auto index : Util<Dimension>::getRange(min, size)) {
        vec v = Util<Dimension>::array2Vec<size_t>(index) - one;
        _surrounding.push_back(v);
      }
      _grid = std::dynamic_pointer_cast<SpatialHash<Dimension>>(std::make_shared< GridHash<Dimension> >(AABB<Dimension>(vec(0),Util<Dimension>::array2Vec(dimension)), 3.0));
    }

    vec getGradient(vec position) {
      vec result(0);
      for (auto dir : _surrounding) {
        float dis = getDiscomfort(position + dir);
        result += dis * dir;
      }
      return result;
    }

    double getDiscomfort(vec position) {
      auto objs = _grid->findObjects(position);
      double result = 0;
      for (auto obj : objs) {
        std::shared_ptr<DiscomfortArea<Dimension>> cast = std::dynamic_pointer_cast<DiscomfortArea<Dimension>>(obj);
        result += cast->getDiscomfort(position);
      }
      return result;
    }

    void addDiscomfortArea(std::shared_ptr<DiscomfortArea<Dimension>> area) {
      _discomfortAreas.insert(area);
      _grid->addObject(area);
    }

    void removeDiscomfortArea(std::shared_ptr<DiscomfortArea<Dimension>> area) {
      _discomfortAreas.erase(area);
      _grid->removeObject(area);
    }

    void updateDiscomfort() {
      for (auto area : _discomfortAreas) {
        _grid->updateObject(area);
      }
    }

  public:
    std::vector<vec>                                       _surrounding    ;
    std::shared_ptr<SpatialHash<Dimension>>                _grid           ;
    float                                                  _scale          ;
    std::set<std::shared_ptr<DiscomfortArea<Dimension>>>   _discomfortAreas;
  };
}