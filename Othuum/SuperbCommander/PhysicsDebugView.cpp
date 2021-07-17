#include "PhysicsDebugView.h"

#include "SuthanusPhysicsLib/PhysicEngine.h"
#include "AthanahCommonLib/BulletDebugDrawer.h"
#include "AhwassaGraphicsLib/BasicRenderer/BasicBoxRenderer.h"
#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Input/Input.h"

namespace Superb {
  PhysicsDebugView::PhysicsDebugView(std::shared_ptr<Suthanus::PhysicEngine> physic,Ahwassa::Window* window, Iyathuum::Key key) {
    _key = key;
    _physic = physic;
    _window = window;

    _debug = std::make_shared<Athanah::BulletDebugDrawer>(_window->camera());
    physic->setDebugDrawer(_debug.get());
  }

  void PhysicsDebugView::update() {
    if (_window->input().getKeyStatus(_key) == Iyathuum::KeyStatus::PRESS && !_pressed) {
      _pressed = true;
      _active = !_active;
    }
    else if (_window->input().getKeyStatus(_key) == Iyathuum::KeyStatus::RELEASE)
      _pressed = false;
  }

  void PhysicsDebugView::draw() {
    if (_active)
    {
      _debug->_box->start();
      _physic->debugDrawWorld();
      _debug->_box->end();
    }
  }

}