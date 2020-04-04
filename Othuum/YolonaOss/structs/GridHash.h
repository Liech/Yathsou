#pragma once

#include "SpatialHash.h"
#include <map>
#include "../Util/Util.h"

namespace YolonaOss {
  template<size_t Dimension>
  class GridHash : public SpatialHash<Dimension> {
    using vec = typedef glm::vec<Dimension, float, glm::defaultp>;
  public:
    GridHash(AABB<Dimension> area, double gridSize) {
      _gridSize = gridSize;
      _area = area;
      std::array<size_t, Dimension> dim;
      for (size_t i = 0; i < Dimension; i++)
        dim[i] = std::ceil(area.getSize()[i] / gridSize);
      _data = std::make_unique<MultiDimensionalArray<std::set<std::shared_ptr<ObjectWithAABB<Dimension>>>, Dimension>>(dim);
    }

    virtual void updateObject(std::shared_ptr<ObjectWithAABB<Dimension>> object) override {
      removeObject(object);
      addObject(object);
    }

    virtual void addObject(std::shared_ptr<ObjectWithAABB<Dimension>> object) {
      std::array<size_t, Dimension> start;
      std::array<size_t, Dimension> size;
      AABB<Dimension> bounds = object->getAABB();

      for (size_t i = 0; i < Dimension; i++) {
        double d = std::floor((std::max((double)bounds.getPosition()[i],0.0) - _area.getPosition()[i]) / (double)_gridSize);
        start[i] = d;
        size[i] = std::ceil((bounds.getPosition()[i] + bounds.getSize()[i] - _area.getPosition()[i]) / _gridSize) - start[i];
      }

      std::set<std::array<size_t, Dimension>> indexes;
      std::set<std::shared_ptr<ObjectWithAABB<Dimension>>> result;
      Util<Dimension>::apply(start, size, [object, &indexes,this](std::array<size_t, Dimension> index) {
        #pragma omp critical
        {     
          indexes.insert(index);
        }
        _data->getRef(index).insert(object);   
        });

      _updateIndex[object] = indexes;
    }

    virtual void removeObject(std::shared_ptr<ObjectWithAABB<Dimension>> object) {
      assert(_updateIndex.count(object));
      for (auto i : _updateIndex[object])
        _data->getRef(i).erase(object);
    }

    virtual std::set<std::shared_ptr<ObjectWithAABB<Dimension>>> findObjects(vec  position) {
      std::array<size_t, Dimension> index;
      for (size_t i = 0; i < Dimension; i++) {
        index[i] = std::floor((std::max(position[i],0.0f) - _area.getPosition()[i]) / _gridSize);
      }
      auto candidates = _data->getRef(index);
      std::set < std::shared_ptr<ObjectWithAABB<Dimension>>> result;
      for (auto candidate : candidates) {
        if (candidate->getAABB().isInside(position))
          result.insert(candidate);
      }
      return result;
    }

    virtual std::set<std::shared_ptr<ObjectWithAABB<Dimension>>> findObjects(AABB<Dimension> position) {
      std::array<size_t, Dimension> start;
      std::array<size_t, Dimension> size;
      AABB<Dimension> bounds = getAABB();

      for (size_t i = 0; i < Dimension; i++) {
        start[i] = std::floor((bounds.getPosition()[i] - _area.getPosition()[i]) / _gridSize);
        size[i] = std::ceil((bounds.getPosition()[i] + bounds.getSize()[i] - _area.getPosition()[i]) / (float)_gridSize) - start[i];
      }
      std::set<std::shared_ptr<ObjectWithAABB<Dimension>>> result;
      Util<Dimension>::apply(start, size, [result,this, position](std::array<size_t, Dimension> index) {
        auto candidates = _data->getRef(index);
        std::set < std::shared_ptr<ObjectWithAABB<Dimension>>> result;
        for (auto candidate : candidates) {
          if (candidate->getAABB().intersects(position)) {
            #pragma omp critical
            {
              result.insert(candidate);
            }
          }
        }
      });
      return result;
    }


    virtual AABB<Dimension> getAABB() override{
      return _area;
    }
  private:


    std::unique_ptr<MultiDimensionalArray<std::set<std::shared_ptr<ObjectWithAABB<Dimension>>>, Dimension>>  _data       ;
    std::map< std::shared_ptr<ObjectWithAABB<Dimension>>, std::set<std::array<size_t, Dimension>>>           _updateIndex;
    AABB<Dimension>                                                                                          _area       ;
    size_t                                                                                                   _gridSize   ;
  };
}