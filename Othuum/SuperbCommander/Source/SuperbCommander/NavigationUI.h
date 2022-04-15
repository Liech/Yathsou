#pragma once

#include "AhwassaGraphicsLib/Input/UIElement.h"

#include <glm/glm.hpp>
#include <memory>
#include <vector>

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
  class UnitsOld;
  class Unit;

  class NavigationUI : public Ahwassa::UIElement {
  public:
    NavigationUI(Ahwassa::Window* w, std::shared_ptr<Suthanus::PhysicEngine>, std::shared_ptr<Suthanus::PhysicNavigationMesh>, UnitsOld&);
    virtual ~NavigationUI() = default;

    bool mouseEvent(const glm::vec2& localPosition, const Iyathuum::Key& button, const Iyathuum::KeyStatus& status) override;

    virtual bool isInside(const glm::vec2&, const Iyathuum::Key&) override;
    std::vector<std::shared_ptr<Unit>> selection();

    glm::vec3 getStart();
    glm::vec3 getEnd();

    void debugDraw();
  private:
    void selectSingle();

    std::shared_ptr<Suthanus::PhysicNavigationNode> mouse(glm::vec2 pos) const;

    Ahwassa::Window*                                _window ;
    std::shared_ptr<Suthanus::PhysicEngine>         _physic ;
    std::shared_ptr<Suthanus::PhysicNavigationMesh> _navMesh;
    UnitsOld&                                       _units  ;

    std::vector<std::shared_ptr<Unit>> _selection;
    glm::vec3 _targetPos;
    glm::vec2 _rectangleStart;
    bool      _rectangleSelectionActive = false;
  };
}