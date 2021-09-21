#pragma once

#include <vector>
#include <memory>
#include <IyathuumCoreLib/lib/glm/glm.hpp>
#include "IyathuumCoreLib/Tree/glmOctree.h"
#include "SuthanusPhysicsLib/PhysicEngine.h"

namespace Suthanus {
  class PhysicEngine;

  struct PhysicNavigationNode {
    glm::vec3 position;
    std::vector<std::shared_ptr<PhysicNavigationNode>> links;
  };

  class PhysicNavigationMesh {
  public:
    PhysicNavigationMesh(const PhysicEngine& engine, const Iyathuum::glmAABB<3>& volume, glm::vec3 seedStart,float sampleDistance = 1, float climbingAngleDeg = 35);

    std::vector<glm::vec3> getNodePositions() const;
    std::vector<std::pair<glm::vec3, glm::vec3>> getLinks() const;

  private:
    void initMesh(glm::vec3 seedStart);   

    std::vector<std::shared_ptr<PhysicNavigationNode>> _nodes;

    Iyathuum::glmAABB<3> _volume;
    const PhysicEngine&  _engine;
    float                _sampleDistance = 1;
    float                _climbAngle     = 35;    
  };
}