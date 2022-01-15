#include "UnitConstructor.h"

#include <iostream>

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
    return _selection->newBox(_startPosition, _blueprint->selectionSize(), false);
  }

  // just in case you need that function also
  glm::quat CreateFromAxisAngle(glm::vec3 axis, float angle)
  {
    float halfAngle = angle * .5f;
    float s = (float)std::sin(halfAngle);
    glm::quat q;
    q.x = axis.x * s;
    q.y = axis.y * s;
    q.z = axis.z * s;
    q.w = (float)std::cos(halfAngle);
    return q;
  }

  glm::quat LookAt(glm::vec3 sourcePoint, glm::vec3 destPoint, glm::vec3 up)
  {
    glm::vec3 forward = glm::vec3(1, 0, 0);

    glm::vec3 forwardVector = glm::normalize(destPoint - sourcePoint);

    float dot = glm::dot(forward, forwardVector);

    if (std::abs(dot - (-1.0f)) < 0.000001f)
    {
      return glm::quat(up.x, up.y, up.z, 3.1415926535897932f);
    }
    if (std::abs(dot - (1.0f)) < 0.000001f)
    {
      return glm::identity<glm::quat>();
    }

    float rotAngle = (float)std::acos(dot);
    glm::vec3 rotAxis = glm::cross(forward, forwardVector);
    rotAxis = glm::normalize(rotAxis);
    return CreateFromAxisAngle(rotAxis, rotAngle);
  }

  std::shared_ptr<Suthanus::Box> UnitConstructor::getPhysic() const {    
    auto result = _physic->newBox(_startPosition, _blueprint->physic().meshExtents(), false);
    return result;
  }

  std::shared_ptr<const Athanah::Blueprint> UnitConstructor::getBlueprint() const {
    return _blueprint;
  }

  std::string UnitConstructor::getId() const {
    return _id;
  }
}