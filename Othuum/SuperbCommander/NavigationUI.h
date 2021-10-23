#pragma once

#include "AhwassaGraphicsLib/Input/UIElement.h"

#include "IyathuumCoreLib/lib/glm/glm.hpp"
#include <memory>

namespace Ahwassa {
  class Window;
}

namespace Suthanus {
  class PhysicEngine;
  class PhysicNavigationMesh;
  struct PhysicNavigationNode;
}

//window, physic, navmesh
namespace Superb {
  class Units;

  class NavigationUI : public Ahwassa::UIElement {
  public:
    NavigationUI(Ahwassa::Window* w, std::shared_ptr<Suthanus::PhysicEngine>, std::shared_ptr<Suthanus::PhysicNavigationMesh>, std::shared_ptr<Units>);

    bool mouseClickEvent(glm::vec2 localPosition, Iyathuum::Key button) override;

    virtual bool isInside(glm::vec2, Iyathuum::Key) override;

    glm::vec3 getStart();
    glm::vec3 getEnd();

    void debugDraw();
  private:
    std::shared_ptr<Suthanus::PhysicNavigationNode> mouse(glm::vec2 pos) const;

    Ahwassa::Window*                                _window ;
    std::shared_ptr<Suthanus::PhysicEngine>         _physic ;
    std::shared_ptr<Suthanus::PhysicNavigationMesh> _navMesh;
    std::shared_ptr<Units>                          _units  ;

    glm::vec3 _end ;
    glm::vec3 _start;
  };
}