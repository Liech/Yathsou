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
    setLocalPosition(Iyathuum::glmAABB<2>(glm::vec2(0, 0), w->camera()->getResolution()));
  }

  void NavigationUI::debugDraw() {
    _window->renderer().box().start();
    _window->renderer().box().drawDot(_start , 0.5f, Iyathuum::Color(0, 0, 255));
    _window->renderer().box().drawDot(_end, 0.5f, Iyathuum::Color(255, 0, 255));
    _window->renderer().box().end();
  }

  bool NavigationUI::mouseClickEvent(glm::vec2 localPosition, Iyathuum::Key button) {
    if (Iyathuum::Key::MOUSE_BUTTON_RIGHT == button) {
      auto node = mouse(localPosition);
      if (node) {
        _end = node->position;
        return true;
      }
    }
    if (Iyathuum::Key::MOUSE_BUTTON_LEFT == button) {
      auto node = mouse(localPosition);
      if (node) {
        _start = node->position;
        return true;
      }
    }
    return false;
  }

  std::shared_ptr<Suthanus::PhysicNavigationNode> NavigationUI::mouse(glm::vec2 localPosition) const{
    glm::vec2 cursorPos = localPosition;
    cursorPos[1] = _window->getHeight() - cursorPos[1];
    glm::vec3 ray = _window->camera()->getPickRay(cursorPos);
    glm::vec3 origin = _window->camera()->getPosition();
    glm::vec3 hit;
    bool doesHit = _physic->raycast(origin, ray, hit);

    if (doesHit) {
      return _navMesh->findNext(hit);
    }
    return nullptr;
  }

  bool NavigationUI::isInside(glm::vec2 pos, Iyathuum::Key k) {
    if (!Ahwassa::UIElement::isInside(pos,k))
      return false;
    if (k != Iyathuum::Key::MOUSE_BUTTON_RIGHT && k != Iyathuum::Key::KEY_NONE)
      return false;
    //if (!mouse(pos))
    //  return false;
    return true;
  }

}