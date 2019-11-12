#pragma once

#include <memory>
#include "structs/Dijkstra.h"
#include "structs/NMTree.h"
#include "structs/NMTreeNeighbourIndex.h"
  

namespace YolonaOss {

  template <size_t ArraySize, size_t Dimension>
  class NavigationMap {
    using vec = std::array<double, Dimension>;
    using Tree  = NMTree<bool, ArraySize, Dimension, YolonaOss::TreeMergeBehavior::Max, false>;
    using TreeI = NMTreeNeighbourIndex<bool, ArraySize, Dimension, YolonaOss::TreeMergeBehavior::Max, false>;
  public:
    NavigationMap(std::shared_ptr<TreeI> map) {
      updateIndex(map);
    }


    vec getTargetPosition() {

    }

    void updateIndex(std::shared_ptr<TreeI> index) {
      _index = index;
    }
  private:
    std::shared_ptr<TreeI> _index;
    vec                    _targetPosition;
    Dijkstra<Tree*>        _path;
  };
}