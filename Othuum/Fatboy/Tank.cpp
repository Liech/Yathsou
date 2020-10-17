#include "Tank.h"
#include "SuthanusPhysicsLib/PhysicEngine.h"
#include "SuthanusPhysicsLib/Vehicle.h"
#include "TankTower.h"
#include "YolonaOss/Renderer/BoxRenderer.h"
#include "SuthanusPhysicsLib/ArtilleryAim.h"
#include "HaasScriptingLib/ScriptEngine.h"
#include "Context.h"
#include "BulletPool.h"

namespace Fatboy
{
  Tank::Tank(std::shared_ptr<Context> context)
  {
    _context = context;
  }

  void Tank::load(YolonaOss::GL::DrawSpecification* spec)
  {
    _spec = spec;
    _physBody = _context->physic()->newVehicle(glm::vec3(0, 2, 0));

    _tower = std::make_shared<TankTower>(*_physBody, glm::vec3(0, 0.5f, 0), glm::vec3(1, 0, 0));
    _tower->load(spec);
  }

  void Tank::update()
  {
    _tower->update();
  }

  void Tank::draw()
  {
    YolonaOss::BoxRenderer::start();
    glm::mat4 transformVehicle = _physBody->getTransformation();
    transformVehicle = glm::scale(transformVehicle, _physBody->getSize());
    transformVehicle = glm::translate(transformVehicle, glm::vec3(-0.5, -0.5, -0.5));
    YolonaOss::BoxRenderer::draw(transformVehicle, glm::vec4(0, 0.4, 1, 1));
    YolonaOss::BoxRenderer::end();
    _tower->draw();
  }

  void Tank::fire()
  {
    
    auto bullet = _context->physic()->newSphere(_tower->getGlobalPosition(), 0.1f, true);
    glm::vec3 v =  _tower->getCurrentGlobalDirection() * _firePower;
    bullet->setVelocity(v);
    _context->bullets()->addBullet(bullet);
    std::weak_ptr<Suthanus::Sphere> b = bullet;
    bullet->setCollisionCallback([this,b](std::weak_ptr < Suthanus::PhysicObject > other)
      {
        if (std::shared_ptr<Suthanus::Sphere> lock = b.lock())
        {
          std::shared_ptr<Suthanus::PhysicObject> lOther = other.lock();
          //if (!std::dynamic_pointer_cast<Suthanus::Sphere>(lOther))
          //  _bullets.erase(lock);
        }
      });
  }

  void Tank::setAcceleration(float value)
  {
    _physBody->setAcceleration(std::clamp(value, -_physBody->maxAcceleration(), _physBody->maxAcceleration()));
  }

  void Tank::setSteering(float value)
  {
    _physBody->setSteering(std::clamp(value,-_physBody->maxSteering(), _physBody->maxSteering()));
  }

  void Tank::setTarget(glm::vec3 target)
  {
    _aimTarget = target;
    glm::vec3 diff = target - _tower->getGlobalPosition();
    glm::vec3 aim = Suthanus::ArtilleryAim::aimSpring(diff, _firePower, false);
    aim.y = aim.y;
    if (glm::length(aim) > 0)
      _tower->setGlobalTargetDirection(aim);
  }

  float Tank::maxAcceleration()
  {
    return _physBody->maxAcceleration();
  }

  float Tank::maxSteering()
  {
    return _physBody->maxSteering();
  }

  glm::vec3 Tank::getPosition()
  {
    return _physBody->getPosition();
  }
}