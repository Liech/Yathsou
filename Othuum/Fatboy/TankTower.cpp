#include "TankTower.h"
#include "YolonaOss/Renderer/BoxRenderer.h"
#include "GameConfiguration.h"
#include "IyathuumCoreLib/Lib/glm/gtx/vector_angle.hpp""

namespace Fatboy
{
  TankTower::TankTower(Suthanus::PhysicObject& attachTo, glm::vec3 offset, glm::vec3 startDirection)
    : _attachedTo(attachTo), _offset(offset), _direction(startDirection),_targetDirection(startDirection)
  {
  }

  void TankTower::load(YolonaOss::GL::DrawSpecification*)
  {

  }

  void TankTower::update()
  {
    rotateTowardsTarget();
  }

  void TankTower::rotateTowardsTarget()
  {
    //Fatboy::GameConfiguration::instance().PhysicTicksPerSecond
    //X/Y getrennt rotieren
    //maximale gesamtgeschwindigkeit 
    //maximal erreichbare winkel

    _direction       = glm::normalize(_direction);
    _targetDirection = glm::normalize(_targetDirection);
    glm::vec3 direction_YLess       = glm::vec3(_direction.x      , 0, _direction.z      );
    glm::vec3 targetDirection_YLess = glm::vec3(_targetDirection.x, 0, _targetDirection.z);
    glm::vec3 up     = glm::vec3(0, 1, 0);
    glm::vec3 axis   = glm::cross(_direction, _targetDirection);
    float angle      = glm::orientedAngle(direction_YLess, targetDirection_YLess,up);
    if (angle > glm::pi<float>())
      angle -= glm::pi<float>() * 2;
    _direction       = glm::rotate(_direction, angle * 0.01f, up);
  }

  glm::vec3 TankTower::getGlobalPosition()
  {
    glm::vec4 offsetTransformed = _attachedTo.getTransformation() * glm::vec4(_offset, 1);
    glm::vec3 result = glm::vec3(offsetTransformed.x, offsetTransformed.y, offsetTransformed.z);
    return result;
  }

  glm::vec3 TankTower::getCurrentGlobalDirection()
  {
    glm::vec4 dirTransformed = _attachedTo.getTransformation() * glm::vec4(_offset + _direction, 1);
    glm::vec3 result = glm::vec3(dirTransformed.x, dirTransformed.y, dirTransformed.z);
    return result;
  }

  void TankTower::draw()
  {
    YolonaOss::BoxRenderer::start();
    YolonaOss::BoxRenderer::drawDot(getGlobalPosition(), glm::vec3(0.05f), glm::vec4(1, 1, 0, 1));
    YolonaOss::BoxRenderer::drawLine(getGlobalPosition(), getCurrentGlobalDirection(), 0.01, glm::vec4(1, 1, 0, 1));
    YolonaOss::BoxRenderer::drawLine(getGlobalPosition(), getGlobalPosition() + _targetDirection, 0.05, glm::vec4(1, 0,1, 1));
    YolonaOss::BoxRenderer::end();
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
    _targetDirection = glm::normalize(dir);
  }   
}