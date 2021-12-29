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
    if (_navUIDebugDraw)
      _navUI->debugDraw();
  }

  Ahwassa::ArcBallCamera& Control::arcCamera() {
    return *_arcCam;
  }

  void Control::save(nlohmann::json& output) {
    output["NavigationUIDebugView"] = _navUIDebugDraw;
  }

  void Control::load(nlohmann::json& input) {
    _navUIDebugDraw = input["NavigationUIDebugView"];
  }

  void Control::start() {
    _freeCam = std::make_unique<Ahwassa::FreeCamera   >(_window.camera(), _window.input(), Iyathuum::Key::KEY_F3);
    _arcCam = std::make_unique<Ahwassa::ArcBallCamera>(_window.camera(), _window.input(), Iyathuum::Key::KEY_F4);
    _window.input().addUIElement(_freeCam.get());
    _window.input().addUIElement(_arcCam.get());
    _navUI = std::make_unique <Superb::NavigationUI>(&_window, _game.physic().physic(), _game.terrain().world().navMesh(), _game.units().units());
    _window.input().addUIElement(_navUI.get());
    _driveUI = std::make_unique<Superb::DriveInterface>(_window.input());
  }
}