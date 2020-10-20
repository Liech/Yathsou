#include "Unit.h"
#include "SuthanusPhysicsLib/PhysicEngine.h"
#include "SuthanusPhysicsLib/Vehicle.h"
#include "TankTower.h"
#include "YolonaOss/Renderer/BoxRenderer.h"
#include "SuthanusPhysicsLib/ArtilleryAim.h"
#include "HaasScriptingLib/ScriptEngine.h"
#include "Context.h"
#include "BulletPool.h"
#include "Bullet.h"

namespace Fatboy
{
  Unit::Unit(std::shared_ptr<Context> context)
  {
    _context = context;
  }

  void Unit::load(YolonaOss::GL::DrawSpecification* spec)
  {
    _spec = spec;
    _physBody = _context->physic()->newVehicle(_startPosition);

    _tower = std::make_shared<TankTower>(*_physBody, glm::vec3(0, 0.5f, 0), glm::vec3(1, 0, 0));
    _tower->load(spec);
  }

  void Unit::setStartPosition(glm::vec3 startPos)
  {
    _startPosition = startPos;
  }

  void Unit::update()
  {
    _tower->update();
  }

  void Unit::draw()
  {
    YolonaOss::BoxRenderer::start();
    glm::mat4 transformVehicle = _physBody->getTransformation();
    transformVehicle = glm::scale(transformVehicle, _physBody->getSize());
    transformVehicle = glm::translate(transformVehicle, glm::vec3(-0.5, -0.5, -0.5));
    YolonaOss::BoxRenderer::draw(transformVehicle, glm::vec4(0, 0.4, 1, 1));
    YolonaOss::BoxRenderer::end();
    _tower->draw();
  }

  void Unit::fire()
  {    
    glm::vec3 v =  _tower->getCurrentGlobalDirection() * _firePower;
    std::shared_ptr<Bullet> bullet = std::make_shared < Bullet>(_context, _tower->getGlobalPosition(),v);
    _context->bullets()->addBullet(bullet);
  }

  void Unit::setAcceleration(float value)
  {
    _physBody->setAcceleration(std::clamp(value, -_physBody->maxAcceleration(), _physBody->maxAcceleration()));
  }

  void Unit::setSteering(float value)
  {
    _physBody->setSteering(std::clamp(value,-_physBody->maxSteering(), _physBody->maxSteering()));
  }

  void Unit::setTarget(glm::vec3 target)
  {
    _aimTarget = target;
    glm::vec3 diff = target - _tower->getGlobalPosition();
    glm::vec3 aim = Suthanus::ArtilleryAim::aimSpring(diff, _firePower, false);
    aim.y = aim.y;
    if (glm::length(aim) > 0)
      _tower->setGlobalTargetDirection(aim);
  }

  float Unit::maxAcceleration()
  {
    return _physBody->maxAcceleration();
  }

  float Unit::maxSteering()
  {
    return _physBody->maxSteering();
  }

  glm::vec3 Unit::getPosition()
  {
    return _physBody->getPosition();
  }

  std::vector<std::shared_ptr<Suthanus::PhysicObject>> Unit::getPhysics()
  {
    return { _physBody };
  }
}