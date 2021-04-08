#include "TankTower.h"
#include "AhwassaGraphicsLib/BasicRenderer/BasicBoxRenderer.h"
#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Core/Renderer.h"
#include "GameConfiguration.h"
#include "IyathuumCoreLib/Lib/glm/gtx/vector_angle.hpp""
#include <iostream>

namespace Fatboy
{
  TankTower::TankTower(Suthanus::PhysicObject& attachTo, glm::vec3 offset, glm::vec3 startDirection, Ahwassa::Window* w)
    : _attachedTo(attachTo), _offset(offset),_targetDirection(startDirection), Ahwassa::Drawable(w)
  {
    setGlobalTargetDirection(startDirection);
    _direction = glm::lookAt(glm::vec3(0,0,0), glm::vec3(0, 0, 0) + _targetDirection, glm::vec3(0, 1, 0));
    _box = std::make_shared<Ahwassa::BasicBoxRenderer>(w->camera());
  }

  void TankTower::update()
  {
    rotateTowardsTargetDir();
    updateYRotationTarget();
  }

  void TankTower::rotateTowardsTargetDir(){
    glm::quat target = glm::lookAt(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0) + _targetDirection, glm::vec3(0, 1, 0));
    glm::vec3 current = getCurrentDirection();
    glm::vec3 future = getTargetDirection();
    glm::vec3 cross = glm::cross(current, future);
    float angle = glm::abs(glm::orientedAngle(current,future,cross));
    float angleMovement = std::clamp(angle, -getTurnRadianPerTick(), getTurnRadianPerTick());
    if (angle < getTurnRadianPerTick())
      _direction = target;
    else 
      _direction = glm::slerp(_direction, target, angleMovement / angle);
  }

  void TankTower::updateYRotationTarget(){
    glm::vec3 up = glm::vec4(0, 1, 0, 1);
    glm::vec3 future = getTargetDirection();
    glm::vec3 cross = glm::cross(up, future);
    float angle = glm::abs(glm::orientedAngle(up, future, cross));

    float constexpr toRad = glm::pi<float>() / 180.0f;
    float maxAimUpRadian = _maxAimUp * toRad;
    float maxAimDownRadian = glm::pi<float>() - _maxAimDown * toRad;

    float rotToUp = maxAimUpRadian - angle;
    float rotToDown = maxAimDownRadian - angle;

    if (angle > maxAimDownRadian)
      _targetDirection = glm::vec4(glm::rotate(future, rotToDown, cross), 1);
    if (angle < maxAimUpRadian)
      _targetDirection = glm::vec4(glm::rotate(future, rotToUp, cross), 1);
  }

  float TankTower::getTurnRadianPerTick()
  {
    float toRad = glm::pi<float>() / 180.0f;
    return _turnSpeed * toRad / GameConfiguration::instance().TicksPerSecond;
  }

  glm::vec3 TankTower::getCurrentDirection()
  {
    auto mat = glm::toMat4(_direction);
    glm::vec4 dir = glm::vec4(0, 0, 1,1);
    glm::vec4 dirTransformed = dir*mat;
    glm::vec3 result = -glm::vec4(dirTransformed.x, dirTransformed.y, dirTransformed.z, dirTransformed.w) / dirTransformed.w;
    return glm::normalize(result);
  }
  
  glm::vec3 TankTower::getCurrentGlobalDirection()
  {
    glm::vec3 result = _attachedTo.getRotationTransformation() * glm::vec4(getCurrentDirection(),1);
    return result;
  }

  void TankTower::draw()
  {
    _box->start();
    _box->drawDot(getGlobalPosition(), glm::vec3(0.05f), Iyathuum::Color(255, 255, 0));
    _box->drawLine(getGlobalPosition(), getGlobalPosition() + getCurrentGlobalDirection(), 0.01, Iyathuum::Color(255, 255, 0));
    _box->drawLine(getGlobalPosition(), getGlobalPosition() + getGlobalTargetDirection(), 0.05 , Iyathuum::Color(255, 0,255 ));

    glm::vec3 up     =  glm::vec4(0,1,0,1);
    glm::vec3 future = getTargetDirection();
    glm::vec3 cross  = glm::cross(up, future);
    float angle = glm::abs(glm::orientedAngle(up, future, cross));

    float constexpr toRad = glm::pi<float>() / 180.0f;
    float maxAimUpRadian = _maxAimUp * toRad;
    float maxAimDownRadian = glm::pi<float>()-_maxAimDown * toRad;
    float rotToUp = maxAimUpRadian - angle;
    float rotToDown = maxAimDownRadian - angle;

    glm::vec3 maxUp = _attachedTo.getRotationTransformation() * glm::vec4(glm::rotate(future, rotToUp, cross),1);
    glm::vec3 maxDown = _attachedTo.getRotationTransformation() * glm::vec4(glm::rotate(future, rotToDown, cross),1);
    _box->drawLine(getGlobalPosition(), getGlobalPosition() + maxUp  , 0.005, Iyathuum::Color(0, 255, 255));
    _box->drawLine(getGlobalPosition(), getGlobalPosition() + maxDown, 0.005, Iyathuum::Color(0, 255, 255));
    _box->end();
  }

  float TankTower::getMaxAimUp()
  {
    return _maxAimUp;
  }

  float TankTower::getMaxAimDown()
  {
    return _maxAimDown;
  }

  float TankTower::getTurnSpeed()
  {
    return _turnSpeed;
  }

  glm::vec3 TankTower::getTargetDirection()
  {
    return _targetDirection;
  }

  glm::vec3 TankTower::getGlobalTargetDirection()
  {
    glm::vec4 result = _attachedTo.getRotationTransformation() * glm::vec4(_targetDirection, 1);
    return result;
  }

  void TankTower::setMaxAimUp(float maxValue)
  {
    _maxAimUp = maxValue;
  }

  void TankTower::setMaxAimDown(float maxValue)
  {
    _maxAimDown = maxValue;
  }

  void TankTower::setTurnSpeed(float degreePerSecond)
  {
    _turnSpeed = degreePerSecond;
  }

  void TankTower::setGlobalTargetDirection(glm::vec3 dir)
  {
    glm::vec3 d = glm::inverse(_attachedTo.getRotationTransformation())*glm::vec4(dir,1);
    _targetDirection = glm::normalize(d);
    updateYRotationTarget();
  }

  glm::vec3 TankTower::getGlobalPosition()
  {
    glm::vec4 pos = _attachedTo.getTransformation() * glm::vec4(_offset, 1);
    glm::vec3 result = glm::vec3(pos.x, pos.y, pos.z);
    return result;
  }
}