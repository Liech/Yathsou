#include "Protagonist.h"

#include "YolonaOss/Renderer/BoxRenderer.h"
#include "YolonaOss/OpenGL/Window.h"
#include "SuthanusPhysicsLib/PhysicTest.h"
#include "SuthanusPhysicsLib/Vehicle.h"
#include <IyathuumCoreLib/lib/glm/gtc/matrix_transform.hpp>
#include "IyathuumCoreLib/lib/glm/gtc/type_ptr.hpp"

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
    if (isPressed(YolonaOss::GL::Key::KEY_ENTER))
    {
      _physBody->setPosition(getStartPos());
      _physBody->setVelocity(glm::vec3(0, 0, 0));
      _physBody->setAngularVelocity(glm::vec3(0, 0, 0));
      _physBody->setRotation(glm::quat(glm::vec3(0,0,0)));
    }

  }

  glm::vec3 Protagonist::getPosition()
  {
    return _physBody->getPosition();
  }

}