#include "Control.h"

#include "AhwassaGraphicsLib/lib/DearIMGUI/imgui.h"

#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Core/Camera.h"
#include "AhwassaGraphicsLib/Input/Input.h"
#include "AhwassaGraphicsLib/Input/FreeCamera.h"
#include "AhwassaGraphicsLib/Input/ArcBallCamera.h"

#include "SuthanusPhysicsLib/Objects/Box.h"
#include "SuperbCommander/DriveInterface.h"
#include "SuperbCommander/NavigationUI.h"
#include "SuperbCommander/World.h"
#include "SuperbCommander/Unit.h"

#include "Game.h"
#include "Terrain.h"
#include "Units.h"
#include "Physic.h"

namespace Superb {
  Control::Control(Ahwassa::Window& w, Game& g) : _game(g), _window(w) {
    _freeCam = std::make_unique<Ahwassa::FreeCamera   >(w.camera(), w.input(), Iyathuum::Key::KEY_F3);
    _arcCam  = std::make_unique<Ahwassa::ArcBallCamera>(w.camera(), w.input(), Iyathuum::Key::KEY_F4);
    w.input().addUIElement(_freeCam.get());
    w.input().addUIElement(_arcCam.get());
    _navUI = std::make_unique <Superb::NavigationUI>(&w, g.physic().physic(), g.terrain().world().navMesh(), g.units().units());
    w.input().addUIElement(_navUI.get());
    _driveUI = std::make_unique<Superb::DriveInterface>(w.input());
  }

  void Control::menu() {    
    ImGui::Checkbox("Navigation Debug View", &_navUIDebugDraw);
  }

  void Control::update() {
    _driveUI->update();

    if (arcCamera().isFocus() && _navUI->selection().size() > 0) {
      _window.camera()->setTarget(_navUI->selection()[0]->getPosition());
      _driveUI->setTarget(_navUI->selection()[0]->getPhysic());
    }
    else
      _driveUI->setTarget(nullptr);

  }

  void Control::debugDraw() {
    _navUI->debugDraw();
  }

  Ahwassa::ArcBallCamera& Control::arcCamera() {
    return *_arcCam;
  }
}