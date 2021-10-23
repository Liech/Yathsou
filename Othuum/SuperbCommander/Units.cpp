#include "Units.h"

#include "SelenNavigationLib/Maps/DirectDistanceMap.h"
#include "AhwassaGraphicsLib/BasicRenderer/BasicBoxRenderer.h"
#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Core/Renderer.h"

namespace Superb {
  Units::Units(Ahwassa::Window* w) {
    _window = w;
    _map = std::make_shared<Selen::DirectDistanceMap<3>>();
    auto firstUnit = std::make_shared<Selen::NavigationAgent<3>>(glm::vec3(0),glm::vec3(0));
    firstUnit->setMap(_map);
    _units.push_back(firstUnit);
  }

  void Units::setTarget(glm::vec3 pos) {
    _map->setTarget(pos);
  }

  void Units::update() {
    for (auto unit : _units)
      unit->updatePosition();
  }

  void Units::draw() {

  }

  void Units::debugDraw() {
    _window->renderer().box().start();
    for(auto unit : _units)
      _window->renderer().box().drawDot(unit->getPosition(), 0.5f, Iyathuum::Color(255, 128, 30));
    _window->renderer().box().end();
  }
}