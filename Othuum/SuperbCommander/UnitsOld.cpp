#include "UnitsOld.h"

#include "SelenNavigationLib/Maps/DirectDistanceMap.h"
#include "SelenNavigationLib/MapGroup.h"

#include "AthanahCommonLib/SupCom/Gamedata/BlueprintFactory.h"

#include "SuthanusPhysicsLib/PhysicEngine.h"
#include "SuthanusPhysicsLib/Objects/Box.h"
#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Core/Camera.h"

#include "UnitConstructor.h"

namespace Superb {
  UnitsOld::UnitsOld(Athanah::Gamedata& gamedata, std::shared_ptr<Suthanus::PhysicEngine> physic) :
   _gamedata(gamedata){
    _physic     = physic;
    _selection  = std::make_shared<Suthanus::PhysicEngine>();

    auto rnd = []() {return (rand() % 500) / 500.0f; };
    for (int i = 0; i < 200; i++) {      
      glm::vec3 pos(rnd()*400 + 20, 100, rnd()*400 + 20);
      spawnUnit(pos);
    }
  }

  void UnitsOld::update() {
    _selection->update();
    for (auto unit : _units) {
      unit.second->update();
      //unit.second->agent->updatePosition();
      //unit.second->selector->setPosition(unit.second->agent->getPosition());
    }
  }

  std::vector<std::shared_ptr<Unit>> UnitsOld::select(glm::vec3 pos, glm::vec3 dir) {
    glm::vec3 hit;
    std::shared_ptr<Suthanus::Box> obj = std::dynamic_pointer_cast<Suthanus::Box>(_selection->raycast(pos, dir, hit));
    
    if (!obj)
      return {};
    return { _units[obj] };
  }

  std::vector<std::shared_ptr<Unit>> UnitsOld::selectCameraRect(glm::vec2 rectangleStart, glm::vec2 rectangleEnd) {
    //auto c = _window->camera();
    //glm::vec3 topLeft  = c->getPickRay(rectangleStart);
    //glm::vec3 botLeft = c->getPickRay(glm::vec2(rectangleStart[0], rectangleEnd[1]));
    //glm::vec3 topRight = c->getPickRay(glm::vec2(rectangleEnd[0], rectangleStart[1]));
    //glm::vec3 botRight = c->getPickRay(rectangleEnd);

    std::vector<std::shared_ptr<Unit>> result;
    //auto frustumQuery = _selection->insideFrustum(c->getPosition(), topLeft, topRight, botLeft, botRight, c->getNearPlane(), c->getFarPlane());
    //for (auto& x : frustumQuery) {
    //  std::shared_ptr<Suthanus::Box> obj = std::dynamic_pointer_cast<Suthanus::Box>(x);
    //  result.push_back(_units[obj]);
    //}
    return result;
  }

  void UnitsOld::spawnUnit(const glm::vec3& position) {
    glm::vec3 groundPos;
    if (nullptr == _physic->raycast(position, glm::vec3(0, -20, 0), groundPos))
      groundPos = position;
    UnitConstructor constructor(_gamedata);//UEL0201
    std::vector<std::string> possibleIDs = { "UEL0201" };//, "URL0309", "XSS0303", "UEL0401"};

    constructor.setId(possibleIDs[rand()%possibleIDs.size()]);
    constructor.setPhysic(_physic);
    constructor.setSelection(_selection);
    constructor.setStartPosition(groundPos + glm::vec3(0,1,0));
    auto firstUnit = std::make_shared<Unit>(constructor);//_gamedata.blueprint().loadModel("UEL0201")
    _units[firstUnit->getSelector()] = firstUnit;
  }

  std::vector<glm::vec3> UnitsOld::PersonalSpaceQuery(const glm::vec3& pos, float maxDistance) const {
    auto physObjects = _selection->insideSphere(pos, maxDistance);
    std::vector<glm::vec3> results;
    for (auto x : physObjects)
      results.push_back(x->getPosition());
    return results;
  }

  std::vector<std::shared_ptr<Unit>> UnitsOld::getUnits() const {
    std::vector<std::shared_ptr<Unit>> result;
    result.reserve(_units.size());
    for (auto x : _units)
      result.push_back(x.second);
    return result;
  }
}