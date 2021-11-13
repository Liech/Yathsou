#include "UnitConstructor.h"

#include "SuthanusPhysicsLib/PhysicEngine.h"
#include "SuthanusPhysicsLib/Objects/Box.h"

namespace Superb {
  UnitConstructor::UnitConstructor(Athanah::Gamedata& gamedata) : _gamedata(gamedata) {

  }

  void UnitConstructor::setId(const std::string& id){
    _id = id;
  }

  void UnitConstructor::setPhysic(std::shared_ptr<Suthanus::PhysicEngine> physic) {
    _physic = physic;
  }

  void UnitConstructor::setSelection(std::shared_ptr<Suthanus::PhysicEngine> selection) {
    _selection = selection;
  }

  void UnitConstructor::setStartPosition(const glm::vec3& pos) {
    _startPosition = pos;
  }

  std::shared_ptr<Suthanus::Box> UnitConstructor::getSelector() const{
    return _selection->newBox(_startPosition, glm::vec3(1, 1, 1), true);
  }

  std::shared_ptr<Suthanus::Box> UnitConstructor::getPhysic() const {
    return _physic->newBox(_startPosition, glm::vec3(1,1,1), true);
  }
}