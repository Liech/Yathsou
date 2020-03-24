#pragma once

#include <glm/glm.hpp>

#include <memory>

#include "Navigation/MapGroup.h"
#include "Navigation/DijkstraMap.h"
#include "Navigation/DiscomfortGridMap.h"

namespace YolonaOss{
  template<size_t Dimension>
  class Landscape{
    using vec = typedef glm::vec<Dimension, float, glm::defaultp>;
    
    private:
      std::shared_ptr<MapGroup         <Dimension>> _allMaps      ;
      std::shared_ptr<DijkstraMap      <Dimension>> _pathfindMap  ;
      std::shared_ptr<DiscomfortGridMap<Dimension>> _discomfortMap;
    
  };
    
}