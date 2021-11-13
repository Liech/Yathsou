#include "NavigationUI.h"

#include "AhwassaGraphicsLib/Core/Camera.h"
#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Core/Renderer.h"
#include "AhwassaGraphicsLib/Input/Input.h"
#include "AhwassaGraphicsLib/BasicRenderer/BasicBoxRenderer.h"
#include "AhwassaGraphicsLib/BasicRenderer/BasicRectangleRenderer.h"

#include "SuthanusPhysicsLib/PhysicEngine.h"
#include "SuthanusPhysicsLib/PhysicNavigationMesh.h"

#include "Units.h"


namespace Superb {
  NavigationUI::NavigationUI(Ahwassa::Window* w, std::shared_ptr<Suthanus::PhysicEngine> physic, std::shared_ptr<Suthanus::PhysicNavigationMesh> nav, std::shared_ptr<Units> units) {
    _units   = units ;
    _window  = w     ;
    _physic  = physic;
    _navMesh = nav   ;
    setLocalPosition(Iyathuum::glmAABB<2>(glm::vec2(0, 0), w->camera()->getResolution()));
  }

  glm::vec3 NavigationUI::getEnd() {
    return _targetPos;
  }

  void NavigationUI::debugDraw() {
    _window->renderer().box().start();
    _window->renderer().box().drawDot(_targetPos, 0.5f, Iyathuum::Color(255, 0, 255));
    for (auto unit : _selection)
      _window->renderer().box().drawDot(unit->getPosition(), 0.1f, Iyathuum::Color(128, 128, 128));
    _window->renderer().box().end();
    if (_rectangleSelectionActive) {
      glm::vec2 mousePos = _window->input().getCursorPos();
      _window->renderer().rectangle().start();
      _window->renderer().rectangle().drawRectangle(_rectangleStart,mousePos- _rectangleStart,Iyathuum::Color(0,0,0,128));
      _window->renderer().rectangle().end();
    }
  }

  bool NavigationUI::mouseEvent(glm::vec2 localPosition, Iyathuum::Key button, Iyathuum::KeyStatus status) {
    glm::vec2 cursorPos = localPosition;
    if (Iyathuum::Key::MOUSE_BUTTON_RIGHT == button && status == Iyathuum::KeyStatus::PRESS) {
      auto node = mouse(localPosition);
      if (node) {
        _targetPos = node->position;
        //for (auto selection : _selection)
        //  selection->map->setTarget(_targetPos);
        return true;
      }
    }
    if (Iyathuum::Key::MOUSE_BUTTON_LEFT == button && status == Iyathuum::KeyStatus::PRESS) {
      _rectangleStart = _window->input().getCursorPos();
      _rectangleSelectionActive = true; 
    }
    if (Iyathuum::Key::MOUSE_BUTTON_LEFT == button && status == Iyathuum::KeyStatus::RELEASE && _rectangleSelectionActive) {
      if (glm::distance(_rectangleStart , cursorPos) < 3) {
        selectSingle();
      } 
      else {

        _selection = _units->selectCameraRect(glm::vec2(_rectangleStart.x, _window->getHeight() - _rectangleStart.y), glm::vec2(localPosition.x, _window->getHeight()- localPosition.y));
      }
      _rectangleSelectionActive = false;
      return true;
    }
    return false;
  }

  std::shared_ptr<Suthanus::PhysicNavigationNode> NavigationUI::mouse(glm::vec2 localPosition) const{
    glm::vec2 cursorPos = localPosition;
    cursorPos[1] = _window->getHeight() - cursorPos[1];
    glm::vec3 ray = _window->camera()->getPickRay(cursorPos);
    glm::vec3 origin = _window->camera()->getPosition();
    glm::vec3 hit;
    bool doesHit = _physic->raycast(origin, ray, hit) != nullptr;

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

  void NavigationUI::selectSingle() {
    bool shift = _window->input().getKeyStatus(Iyathuum::Key::KEY_LEFT_SHIFT) == Iyathuum::KeyStatus::PRESS;

    glm::vec2 cursorPos = _window->input().getCursorPos();
    cursorPos[1] = _window->getHeight() - cursorPos[1];
    glm::vec3 ray = _window->camera()->getPickRay(cursorPos);
    glm::vec3 origin = _window->camera()->getPosition();

    auto newSelection = _units->select(origin, ray);
    if (shift)
      _selection.insert(_selection.end(), newSelection.begin(), newSelection.end());
    else
      _selection = newSelection;
  }

  std::vector<std::shared_ptr<Unit>> NavigationUI::selection() {
    return _selection;
  }

}