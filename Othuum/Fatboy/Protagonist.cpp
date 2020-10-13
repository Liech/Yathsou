#include "Protagonist.h"

#include "YolonaOss/Renderer/BoxRenderer.h"
#include "YolonaOss/Renderer/SphereRenderer.h"
#include "YolonaOss/OpenGL/Window.h"
#include "SuthanusPhysicsLib/PhysicEngine.h"
#include "SuthanusPhysicsLib/Vehicle.h"
#include "SuthanusPhysicsLib/Sphere.h"
#include <IyathuumCoreLib/lib/glm/gtc/matrix_transform.hpp>
#include "IyathuumCoreLib/lib/glm/gtc/type_ptr.hpp"
#include <IyathuumCoreLib/lib/glm/gtx/quaternion.hpp>
#include "TankTower.h"
#include "Tank.h"
#include "SuthanusPhysicsLib/ArtilleryAim.h"


namespace Fatboy
{
  Protagonist::Protagonist(std::shared_ptr<Suthanus::PhysicEngine> physic)
  {
    _physic = physic;
  }

  void Protagonist::load(YolonaOss::GL::DrawSpecification* spec)
  {
    _spec = spec;
    _tank = std::make_shared<Tank>(_physic);
    _tank->load(spec);
  }

  void Protagonist::draw()
  {
    YolonaOss::SphereRenderer::start();
    for (auto sphere : _bullets) {
      glm::mat4 transform = sphere->getTransformation();
      transform = glm::scale(transform, glm::vec3(sphere->getRadius(), sphere->getRadius(), sphere->getRadius()));
      YolonaOss::SphereRenderer::draw(transform, glm::vec4(0, 0.4, 1, 1));
    }
    YolonaOss::SphereRenderer::end();

    _tank->draw();
  }

  void Protagonist::update()
  {
    handleInput();
    handlePicking();
    _tank->update();
  }

  void Protagonist::handlePicking()
  {
    glm::vec2 pos = _spec->getWindow()->getCursorPos();
    glm::vec3 camPos  = _spec->getCam()->getPosition();
    glm::vec3 pickDir = _spec->getCam()->getPickRay((float)pos.x, (float)pos.y);
    glm::vec3 hitPoint;
    bool hit = _physic->raycast(camPos, pickDir, hitPoint);
    if (hit)
    {
      _tank->setTarget(hitPoint);
    }
  }

  void Protagonist::handleInput()
  {
    auto isPressed = [this](YolonaOss::GL::Key key) {
      return _spec->getWindow()->getKeyStatus(key) == YolonaOss::GL::KeyStatus::PRESS;
    };
    if (isPressed(YolonaOss::GL::Key::KEY_W))
    {
      _tank->setAcceleration(_tank->maxAcceleration());
    }
    else if (isPressed(YolonaOss::GL::Key::KEY_S))
    {
      _tank->setAcceleration(-_tank->maxAcceleration());
    }
    else
      _tank->setAcceleration(0);
    if (isPressed(YolonaOss::GL::Key::KEY_A))
    {
      _tank->setSteering(_tank->maxSteering());
    }
    else if (isPressed(YolonaOss::GL::Key::KEY_D))
    {
      _tank->setSteering(-_tank->maxSteering());
    }
    else
      _tank->setSteering(0);
    if (isPressed(YolonaOss::GL::Key::KEY_SPACE) && !_pressed)
    {
      //auto bullet = _physic->newSphere(_tower->getGlobalPosition(), 0.1f, true);
      //glm::vec3 v =  _tower->getCurrentGlobalDirection() * firePower;
      //bullet->setVelocity(v);
      //_bullets.insert(bullet);
      //std::weak_ptr<Suthanus::Sphere> b = bullet;
      //bullet->setCollisionCallback([this,b](std::weak_ptr < Suthanus::PhysicObject > other)
      //  {
      //    if (std::shared_ptr<Suthanus::Sphere> lock = b.lock())
      //    {
      //      std::shared_ptr<Suthanus::PhysicObject> lOther = other.lock();
      //      //if (!std::dynamic_pointer_cast<Suthanus::Sphere>(lOther))
      //      //  _bullets.erase(lock);
      //    }
      //  });
      _tank->fire();
      _pressed = true;
    }
    else if (!isPressed(YolonaOss::GL::Key::KEY_SPACE))
      _pressed = false;
    if (isPressed(YolonaOss::GL::Key::KEY_ENTER))
    {
      //_physBody->setPosition(getStartPos());
      //_physBody->setVelocity(glm::vec3(0, 0, 0));
      //_physBody->setAngularVelocity(glm::vec3(0, 0, 0));
      //_physBody->setRotation(glm::quat(glm::vec3(0,0,0)));

      _tank = std::make_shared<Tank>(_physic);
      _tank->load(_spec);
      _bullets.clear();
    }
  }

  glm::vec3 Protagonist::getPosition()
  {
    return _tank->getPosition();
  }

}