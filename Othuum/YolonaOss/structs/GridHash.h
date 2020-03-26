#pragma once

#include "SpatialHash.h"
#include <map>

namespace YolonaOss {
  template<size_t Dimension>
  class GridHash : public SpatialHash{
    using vec = typedef glm::vec<Dimension, float, glm::defaultp>;
  public:
    GridHash(AABB<Dimension> area, double gridSize) {
      _gridSize = gridSize;
      std::array<size_t, Dimension> dim;
      for (size_t i = 0; i < Dimension; i++)
        dim[i] = std::ceil(area.getSize()[i] / gridSize);
      _data = std::make_unique<MultiDimensionalArray<std::set<ObjectWithAABB<Dimension>>, Dimension>>(dim);
    }

    virtual void updateObject(std::shared_ptr<ObjectWithAABB<Dimension>> object) override {
      removeObject(object);
      addObject(object);
    }

    virtual void addObject(std::shared_ptr<ObjectWithAABB<Dimension>> object) {
      std::array<double, Dimension> min;
      std::array<double, Dimension> max;
      for (size_t i = 0; i < Dimension; i++) {

      }
    }

    virtual void removeObject(std::shared_ptr<ObjectWithAABB<Dimension>> object) {
      assert(_updateIndex.count(object));
      for (auto i : _updateIndex[object])
        _data->getRef(i).erase(object);
    }

    virtual std::set<std::shared_ptr<ObjectWithAABB<Dimension>>> findObjects(vec  position) = 0;
    virtual std::set<std::shared_ptr<ObjectWithAABB<Dimension>>> findObjects(AABB position) = 0;

  private:
    std::unique_ptr<MultiDimensionalArray<std::set<ObjectWithAABB<Dimension>>, Dimension>>         _data       ;
    std::map< std::shared_ptr<ObjectWithAABB<Dimension>>, std::set<std::array<size_t, Dimension>>> _updateIndex;
    AABB<Dimension>                                                                                _area       ;
    size_t                                                                                         _gridSize   ;
  };
}