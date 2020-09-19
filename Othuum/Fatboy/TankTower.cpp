#include "TankTower.h"
#include "YolonaOss/Renderer/BoxRenderer.h"
#include "GameConfiguration.h"

namespace Fatboy
{
  TankTower::TankTower(Suthanus::PhysicObject& attachTo, glm::vec3 offset)
    : _attachedTo(attachTo), _offset(offset)
  {
  }

  void TankTower::load(YolonaOss::GL::DrawSpecification*)
  {

  }

  void TankTower::update()
  {
    //Fatboy::GameConfiguration::instance().PhysicTicksPerSecond
  }

  void TankTower::draw()
  {
    YolonaOss::BoxRenderer::start();
    glm::vec4 offsetTransformed = _attachedTo.getTransformation()*glm::vec4(_offset, 1);
    glm::vec3 drawPos = glm::vec3(offsetTransformed.x, offsetTransformed.y, offsetTransformed.z);
    YolonaOss::BoxRenderer::drawDot(drawPos, glm::vec3(0.05f), glm::vec4(1, 1, 0, 1));
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

  glm::vec3 TankTower::getCurrentGlobalDirection()
  {
    return _direction;
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
    _targetDirection = dir;
  }   
}