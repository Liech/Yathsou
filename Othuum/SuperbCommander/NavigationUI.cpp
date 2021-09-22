#include "NavigationUI.h"

#include "AhwassaGraphicsLib/Core/Camera.h"
#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Core/Renderer.h"
#include "AhwassaGraphicsLib/Input/Input.h"
#include "AhwassaGraphicsLib/BasicRenderer/BasicBoxRenderer.h"

#include "SuthanusPhysicsLib/PhysicEngine.h"
#include "SuthanusPhysicsLib/PhysicNavigationMesh.h"


namespace Superb {
  NavigationUI::NavigationUI(Ahwassa::Window* w, std::shared_ptr<Suthanus::PhysicEngine> physic, std::shared_ptr<Suthanus::PhysicNavigationMesh> nav) {
    _window  = w     ;
    _physic  = physic;
    _navMesh = nav   ;
  }

  void NavigationUI::update() {
    glm::vec2 cursorPos = _window->input().getCursorPos();
    cursorPos[1]        = _window->getHeight()- cursorPos[1];
    glm::vec3 ray       = _window->camera()->getPickRay(cursorPos);
    glm::vec3 origin    = _window->camera()->getPosition();
    glm::vec3 hit;
    bool doesHit = _physic->raycast(origin, ray, hit);

    if (doesHit) {
      _hit = hit;
      auto node = _navMesh->findNext(_hit);
      if(node)
        _node = node->position;
    }
  }

  void NavigationUI::debugDraw() {
    _window->renderer().box().start();
    _window->renderer().box().drawDot(_hit , 0.5f, Iyathuum::Color(0, 0, 255));
    _window->renderer().box().drawDot(_node, 0.5f, Iyathuum::Color(0, 255, 255));
    _window->renderer().box().end();
  }
}