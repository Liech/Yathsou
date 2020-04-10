#pragma once

#include "../structs/MultiDimensionalArray.h"
#include "Aura.h"
#include <set>
#include "../Util/Geometry.h"
#include "../Util/Util.h"
#include "../structs/GridHash.h"
#include "../structs/NMTreeSpatialHash.h"

namespace YolonaOss {
  //You can place Auras in this and query the current aura gradient or value of an arbitrary position
  //Auras are areas that are notified by units. E.g. to recognize friends are near, or too near. See Flocking
  template<size_t Dimension>
  class AuraHolder {
    using vec = typedef glm::vec<Dimension, float, glm::defaultp>;
  public:
    AuraHolder(std::array<size_t, Dimension> dimension, double scale){
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
        bool nonZero = false;
        for (size_t i = 0; i < Dimension; i++)
          if (index[i] != 1)
            nonZero = true;
        if ( nonZero)
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
      //std::cout << "vec: ";
      //for (size_t i = 0; i < Dimension; i++)
      //  std::cout << result[i] << " / ";
      //std::cout << std::endl;
      if (glm::length(result) == 0) return result;
      return glm::normalize(result);
    }

    double getDiscomfort(vec position) {
      auto objs = _grid->findObjects(position);
      double result = 0;
      for (auto obj : objs) {
        std::shared_ptr<Aura<Dimension>> cast = std::dynamic_pointer_cast<Aura<Dimension>>(obj);
        //result += cast->getDiscomfort(position);
      }
      return result;
    }

    void addDiscomfortArea(std::shared_ptr<Aura<Dimension>> area) {
      _aura.insert(area);
      //_grid->addObject(area);
    }

    void removeDiscomfortArea(std::shared_ptr<Aura<Dimension>> area) {
      _aura.erase(area);
      _grid->removeObject(area);
    }

    void updateAuras() {
      for (auto area : _aura) {
        //_grid->updateObject(area);
      }
    }

  public:
    std::vector<vec>                                       _surrounding    ;
    std::shared_ptr<SpatialHash<Dimension>>                _grid           ;
    float                                                  _scale          ;
    std::set<std::shared_ptr<Aura<Dimension>>>             _aura           ;
    NMTreeSpatialHash<Aura<Dimension>, Dimension>          _tree           ;
  };
}