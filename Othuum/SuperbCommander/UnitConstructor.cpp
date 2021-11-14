#include "UnitConstructor.h"

#include "AthanahCommonLib/SupCom/Blueprint/Blueprint.h"
#include "AthanahCommonLib/SupCom/Blueprint/BlueprintPhysic.h"
#include "AthanahCommonLib/SupCom/Gamedata/BlueprintFactory.h"

#include "SuthanusPhysicsLib/PhysicEngine.h"
#include "SuthanusPhysicsLib/Objects/Box.h"

namespace Superb {
  UnitConstructor::UnitConstructor(Athanah::Gamedata& gamedata) : _gamedata(gamedata) {
  }

  void UnitConstructor::setId(const std::string& id){
    _id        = id;
    _blueprint = _gamedata.blueprint().loadModel(id);
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
    return _selection->newBox(_startPosition, _blueprint->selectionSize(), true);
  }

  std::shared_ptr<Suthanus::Box> UnitConstructor::getPhysic() const {    
    return _physic->newBox(_startPosition, _blueprint->physic().meshExtents(), true);
  }

  std::shared_ptr<const Athanah::Blueprint> UnitConstructor::getBlueprint() const {
    return _blueprint;
  }

  std::string UnitConstructor::getId() const {
    return _id;
  }
}