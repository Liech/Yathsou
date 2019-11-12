#pragma once

#include <memory>

#include "../structs/NMTree.h"
#include "../structs/NMTreeNeighbourIndex.h"
#include "NavigationMap.h"
#include "NavigationAgent.h"
//TODO reuse navigationmaps
//TODO make updateTerrain nonblocking

namespace YolonaOss {
  //delivers maps and keeps them uptodate
  //will keep track of discomfort
  template <size_t ArraySize, size_t Dimension>
  class Navigation {
    using vec = std::array<double, Dimension>;
    using Tree = NMTree<bool, ArraySize, Dimension, YolonaOss::TreeMergeBehavior::Max, false>;
    using TreeI = NMTreeNeighbourIndex<bool, ArraySize, Dimension, YolonaOss::TreeMergeBehavior::Max, false>;
    using NavigationMapI = NavigationMap<ArraySize, Dimension>;

  public:
    Navigation(std::shared_ptr<Tree> terrain) {
      _terrain = terrain;
      updateTerrain();
    }

    void updateTerrain() {
      _terrainIndex = std::make_shared < TreeI>(_terrain.get());
      for (auto m : _maps)
        m->updateIndex(_terrainIndex);
    }

    std::shared_ptr<NavigationMapI> getNewMap(vec target) {
      std::shared_ptr<NavigationMapI> result = new std::make_shared<NavigationMapI>(_terrainIndex);
      _maps.push_back(result);
      return result;
    }
  private:
    //MultiDimensionalArray discomfortField;

    std::vector<std::shared_ptr<NavigationMapI>> _maps;
    std::shared_ptr<Tree>  _terrain;
    std::shared_ptr<TreeI> _terrainIndex;
  };
}