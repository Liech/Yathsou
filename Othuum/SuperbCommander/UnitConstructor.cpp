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
    //glm::quat q = glm::lookAt(glm::vec3(0, 0, 0), _normal, glm::vec3(0, 1, 0));
    glm::mat4 rotation = glm::rotate(glm::identity<glm::mat4>(), _direction, _groundNormal);
    glm::vec4 r = glm::vec4(getForwardTangent(),1) * rotation;
    //glm::quat q = glm::lookAt(glm::vec3(0, 0, 0), glm::vec3(r[0], r[1], r[2]), _groundNormal);
    //glm::quat q = LookAt(glm::vec3(0, 0, 0), glm::vec3(r[0], r[1], r[2]), _groundNormal);
    std::cout << "UnitConstructor::getPhysic(glm::vec3(" << r[0] << ", " << r[1] << ", " << r[2] << "), glm::vec3(" << _groundNormal[0]<<", "<< _groundNormal[1] <<", "<< _groundNormal[2] << "));" << std::endl;
    
    glm::vec3 x = getForwardTangent();
    glm::vec3 y = _groundNormal;
    glm::vec3 z = getSidewardsTangent();
    
    //glm::mat4 m = glm::mat4{
    //  x[0],y[0],z[0],0,
    //  x[1],y[1],z[1],0,
    //  x[2],y[2],z[2],0,
    //  x[3],y[3],z[3],1    
    //};
    glm::mat4 m = glm::mat4{
      x[0],x[1],x[2],0,
      y[0],y[1],y[2],0,
      z[0],z[1],z[2],0,
         0,   0,   0,1    
    };

    glm::quat q = glm::quat_cast(m);
    result->setRotation(q);

    return result;
  }

  glm::vec3 UnitConstructor::getSidewardsTangent() const {
    return glm::cross(glm::vec3(1, 0, 0), _groundNormal);
  }

  glm::vec3 UnitConstructor::getForwardTangent() const {
    
    //glm::vec3 cross = glm::cross(glm::vec3(1, 0, 0), _groundNormal);
    glm::vec3 cross = glm::cross(_groundNormal, getSidewardsTangent());
    //glm::vec3 cross = glm::cross(glm::cross(glm::vec3(1, 0, 0), _groundNormal),_groundNormal);
    //glm::vec3 cross = glm::cross(_groundNormal,glm::cross(glm::vec3(1, 0, 0), _groundNormal));
    return cross;
  }

  std::shared_ptr<const Athanah::Blueprint> UnitConstructor::getBlueprint() const {
    return _blueprint;
  }

  std::string UnitConstructor::getId() const {
    return _id;
  }

  void UnitConstructor::setRotation(const glm::vec3& normal) {
    glm::vec3 x = glm::normalize(normal);
    std::cout << "UnitConstructor::setRotation(glm::vec3(" << x[0] << ", " << x[1] << ", " << x[2] << "));" << std::endl;
    //glm::vec3 direction = glm::vec3(1, 0, 0);
    //glm::vec3 z = glm::cross(x, direction);    
    //glm::vec3 y = glm::cross(z,y);
    //glm::vec3 z = glm::cross(x, y);
    //_transformation = glm::mat4 {
    //  x[0],y[0],z[0],0,
    //  x[1],y[1],z[1],0,
    //  x[2],y[2],z[2],0,
    //  x[3],y[3],z[3],1    
    //};
    _groundNormal = x;
  }

  glm::vec3 UnitConstructor::getNormal() const {
    return _groundNormal;
  }
}