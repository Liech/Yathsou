#pragma once

#include <IyathuumCoreLib/lib/glm/glm.hpp>
#include <vector>
#include <memory>

namespace Suthanus {
  class PhysicNavigationMesh;
}

namespace Ahwassa {
  class BoxRenderer;
  class IBox;
  class Camera;
}

namespace Athanah {
  class NavigationMeshDebugDrawer {
  public:
    NavigationMeshDebugDrawer(const Suthanus::PhysicNavigationMesh& mesh, std::shared_ptr<Ahwassa::Camera>);

    void draw();

  private:
    std::shared_ptr<Ahwassa::BoxRenderer>      _renderer;
    std::vector<std::shared_ptr<Ahwassa::IBox>> _boxes   ;

    std::vector<std::pair<glm::vec3, glm::vec3>> _links;
    std::vector<glm::vec3>                       _nodes;
  };
}