#include "PhysicsDebugView.h"

#include "SuthanusPhysicsLib/PhysicEngine.h"
#include "AthanahCommonLib/Physic/BulletDebugDrawer.h"
#include "AhwassaGraphicsLib/Renderer/BasicBoxRenderer.h"
#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Input/Input.h"

namespace Superb {
  PhysicsDebugView::PhysicsDebugView(std::shared_ptr<Suthanus::PhysicEngine> physic,Ahwassa::Window* window) {
    _physic = physic;
    _window = window;

    _debug = std::make_shared<Athanah::BulletDebugDrawer>(_window->camera());
    physic->setDebugDrawer(_debug.get());
  }

  void PhysicsDebugView::draw() {
    _debug->_box->start();
    _physic->debugDrawWorld();
    _debug->_box->end();
  }

}