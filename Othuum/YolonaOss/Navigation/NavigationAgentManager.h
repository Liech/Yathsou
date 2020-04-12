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
    AuraHolder(AABB<Dimension> location) : _tree(location){

    }

    std::set<std::shared_ptr<Aura<Dimension>>> findAuras(vec pos, float radius) {
      return _tree.findRadius(pos, radius);
    }

    void addAura(std::shared_ptr<Aura<Dimension>> area) {
      _aura.insert(area);
      _tree.addObject(area);
    }

    void removeAura(std::shared_ptr<Aura<Dimension>> area) {
      _aura.erase(area);
      _tree.removeObject(area);
    }

    void updateAuras() {
      for (auto area : _aura) {
        _tree.updateObject(area);
      }
    }

  public:
    std::set<std::shared_ptr<Aura<Dimension>>>             _aura           ;
    NMTreeSpatialHash<Aura<Dimension>, Dimension>          _tree           ;
  };
}