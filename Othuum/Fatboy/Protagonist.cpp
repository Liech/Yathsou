#include "Protagonist.h"

#include "YolonaOss/Renderer/BoxRenderer.h"
#include "YolonaOss/Renderer/SphereRenderer.h"
#include "YolonaOss/OpenGL/Window.h"
#include "SuthanusPhysicsLib/PhysicTest.h"
#include "SuthanusPhysicsLib/Vehicle.h"
#include "SuthanusPhysicsLib/Sphere.h"
#include <IyathuumCoreLib/lib/glm/gtc/matrix_transform.hpp>
#include "IyathuumCoreLib/lib/glm/gtc/type_ptr.hpp"
#include <IyathuumCoreLib/lib/glm/gtx/quaternion.hpp>

namespace Fatboy
{
  Protagonist::Protagonist(std::shared_ptr<Suthanus::PhysicTest> physic)
  {
    _physic = physic;
  }

  void Protagonist::load(YolonaOss::GL::DrawSpecification* spec)
  {
    _spec = spec;
    _physBody = _physic->newVehicle(glm::vec3(0, 2, 0));
  }

  void Protagonist::draw()
  {
    YolonaOss::BoxRenderer::start();

    glm::mat4 transformVehicle = _physBody->getTransformation();
    transformVehicle = glm::scale(transformVehicle, _physBody->getSize());
    transformVehicle = glm::translate(transformVehicle, glm::vec3(-0.5, -0.5, -0.5));
    YolonaOss::BoxRenderer::draw(transformVehicle, glm::vec4(0, 0.4, 1, 1));

    YolonaOss::BoxRenderer::end();


    YolonaOss::SphereRenderer::start();
    for (auto sphere : _bullets) {
      glm::mat4 transform = sphere->getTransformation();
      transform = glm::scale(transform, glm::vec3(sphere->getRadius(), sphere->getRadius(), sphere->getRadius()));
      YolonaOss::SphereRenderer::draw(transform, glm::vec4(0, 0.4, 1, 1));
    }
    YolonaOss::SphereRenderer::end();
  }

  void Protagonist::update()
  {
    handleInput();
  }

  void Protagonist::handleInput()
  {
    auto isPressed = [this](YolonaOss::GL::Key key) {
      return _spec->getWindow()->getKeyStatus(key) == YolonaOss::GL::KeyStatus::PRESS;
    };
    if (isPressed(YolonaOss::GL::Key::KEY_W))
    {
      _physBody->setAcceleration(_physBody->maxAcceleration());
    }
    else if (isPressed(YolonaOss::GL::Key::KEY_S))
    {
      _physBody->setAcceleration(-_physBody->maxAcceleration());
    }
    else
      _physBody->setAcceleration(0);
    if (isPressed(YolonaOss::GL::Key::KEY_A))
    {
      _physBody->setSteering(_physBody->maxSteering());
    }
    else if (isPressed(YolonaOss::GL::Key::KEY_D))
    {
      _physBody->setSteering(-_physBody->maxSteering());
    }
    else
      _physBody->setSteering(0);
    if (isPressed(YolonaOss::GL::Key::KEY_SPACE) && !_pressed)
    {
      auto bullet = _physic->newSphere(_physBody->getPosition() - glm::vec3(0,-1,0), 0.1, true);
      glm::vec3 v = glm::vec3(0, 0, 4) * _physBody->getRotation() + glm::vec3(0,4,0);
      bullet->setVelocity(v);
      _bullets.push_back(bullet);
      _pressed = true;
    }
    else if (!isPressed(YolonaOss::GL::Key::KEY_SPACE))
      _pressed = false;
    if (isPressed(YolonaOss::GL::Key::KEY_ENTER))
    {
      _physBody->setPosition(getStartPos());
      _physBody->setVelocity(glm::vec3(0, 0, 0));
      _physBody->setAngularVelocity(glm::vec3(0, 0, 0));
      _physBody->setRotation(glm::quat(glm::vec3(0,0,0)));
      _bullets.clear();
    }
  }

  glm::vec3 Protagonist::getPosition()
  {
    return _physBody->getPosition();
  }

}