#include "Units.h"

#include "SelenNavigationLib/Maps/DirectDistanceMap.h"
#include "SuthanusPhysicsLib/PhysicEngine.h"
#include "SuthanusPhysicsLib/Objects/Box.h"
#include "AhwassaGraphicsLib/BasicRenderer/BasicBoxRenderer.h"
#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Core/Renderer.h"

namespace Superb {
  Units::Units(Ahwassa::Window* w) {
    _window = w;
    
    _selection = std::make_shared<Suthanus::PhysicEngine>();
    
    auto rnd = []() {return (rand() % 100) / 100.0f; };
    for (int i = 0; i < 20; i++) {      
      glm::vec3 pos(rnd()*20 - 10, rnd()*20 - 10, rnd()*20-10);
      auto firstUnit = std::make_shared<Unit>();
      firstUnit->agent = std::make_shared<Selen::NavigationAgent<3>>(pos, glm::vec3(0));
      firstUnit->selector = _selection->newBox(pos, glm::vec3(0.5, 0.5, 0.5), false);
      firstUnit->map = std::make_shared<Selen::DirectDistanceMap<3>>();
      firstUnit->map->setTarget(pos);
      firstUnit->agent->setMap(firstUnit->map);
      _units[firstUnit->selector] = firstUnit;
    }
  }

  void Units::update() {
    _selection->update();
    for (auto unit : _units) {
      unit.second->agent->updatePosition();
      unit.second->selector->setPosition(unit.second->agent->getPosition());
    }
  }

  void Units::draw() {

  }

  void Units::debugDraw() {
    _window->renderer().box().start();
    for(auto unit : _units)
      _window->renderer().box().drawDot(unit.second->agent->getPosition(), 0.5f, Iyathuum::Color(255, 128, 30));
    _window->renderer().box().end();
  }

  std::vector<std::shared_ptr<Unit>> Units::select(glm::vec3 pos, glm::vec3 dir) {
    glm::vec3 hit;
    std::shared_ptr<Suthanus::Box> obj = std::dynamic_pointer_cast<Suthanus::Box>(_selection->raycast(pos, dir, hit));
    if (!obj)
      return {};
    return { _units[obj] };
  }

  std::vector<std::shared_ptr<Unit>> Units::selectCameraRect(glm::vec3 origin, glm::vec3 dir1, glm::vec3 dir2) {
    //auto castResult = _selection->cameraCast(origin,dir1,dir2);
    //std::vector<std::shared_ptr<Unit>> result;
    //for (const auto& obj : castResult)
    //  result.push_back(_units[std::dynamic_pointer_cast<Suthanus::Box>(obj)]);
    //return result;
    return {};
  }
}