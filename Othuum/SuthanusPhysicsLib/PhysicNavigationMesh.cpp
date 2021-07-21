#include "PhysicNavigationMesh.h"
#include <set>
#include "PhysicEngine.h"

namespace Suthanus {
  PhysicNavigationMesh::PhysicNavigationMesh(const PhysicEngine& engine,glm::vec3 seedStart,float sampleDistance, float climbingAngleDeg) {
    _sampleDistance = sampleDistance  ;
    _climbAngle     = climbingAngleDeg;
    initMesh(engine, seedStart);
  }

  void PhysicNavigationMesh::initMesh(const PhysicEngine& engine, glm::vec3 seedStart) {
    PhysicNavigationNode node;
    node.position = seedStart;
    _nodes.push_back(node);
  }

  std::vector<glm::vec3> PhysicNavigationMesh::getNodePositions() const{
    std::vector<glm::vec3> result;

    for (auto x : _nodes)
      result.push_back(x.position);

    return result;
  }

  std::vector<std::pair<glm::vec3, glm::vec3>> PhysicNavigationMesh::getLinks() const{
    std::set<const PhysicNavigationNode*> processedNodes;
    std::vector<std::pair<glm::vec3, glm::vec3>> result;

    for (auto& x : _nodes)
    {
      for (auto link : x.links)
      {
        if (processedNodes.count(link) != 0)
          continue;
        result.push_back(std::make_pair(x.position,link->position));
      }
      processedNodes.insert(&x);
    }

    return result;
  }

}