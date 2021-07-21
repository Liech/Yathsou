#pragma once

#include <vector>
#include <IyathuumCoreLib/lib/glm/glm.hpp>

namespace Suthanus {
  class PhysicEngine;

  struct PhysicNavigationNode {
    glm::vec3 position;
    std::vector<PhysicNavigationNode*> links;
  };

  class PhysicNavigationMesh {
  public:
    PhysicNavigationMesh(const PhysicEngine& engine ,glm::vec3 seedStart,float sampleDistance = 1, float climbingAngleDeg = 35);

    std::vector<glm::vec3> getNodePositions() const;
    std::vector<std::pair<glm::vec3, glm::vec3>> getLinks() const;

  private:
    void initMesh(const PhysicEngine& engine, glm::vec3 seedStart);

    std::vector<PhysicNavigationNode> _nodes;

    float _sampleDistance = 1;
    float _climbAngle     = 35;    
  };
}