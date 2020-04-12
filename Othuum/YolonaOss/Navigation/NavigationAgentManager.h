#pragma once

#include "../structs/MultiDimensionalArray.h"
#include "NavigationAgent.h"
#include <set>
#include "../Util/Geometry.h"
#include "../Util/Util.h"
#include "../structs/GridHash.h"
#include "../structs/NMTreeSpatialHash.h"

namespace YolonaOss {
  //You can place Auras in this and query the current aura gradient or value of an arbitrary position
  //Auras are areas that are notified by units. E.g. to recognize friends are near, or too near. See Flocking
  template<size_t Dimension>
  class NavigationAgentManager {
    using vec = glm::vec<Dimension, float, glm::defaultp>;
  public:
    NavigationAgentManager(AABB<Dimension> location) : _tree(location){

    }

    std::set<std::shared_ptr<NavigationAgent<Dimension>>> findAgents(vec pos, float radius) {
      return _tree.findRadius(pos, radius);
    }

    void addAgent(std::shared_ptr<NavigationAgent<Dimension>> agent) {
      _agents.insert(agent);
      _tree.addObject(agent);
    }

    void removeAgent(std::shared_ptr<NavigationAgent<Dimension>> agent) {
      _agents.erase(agent);
      _tree.removeObject(agent);
    }

    void updateAgents() {
      for (auto agent : _agents) {
        _tree.updateObject(agent);
      }
    }

  public:
    std::set<std::shared_ptr<NavigationAgent<Dimension>>>             _agents         ;
    NMTreeSpatialHash<NavigationAgent<Dimension>, Dimension>          _tree           ;
  };
}