#include "Protagonist.h"

#include "YolonaOss/Renderer/BoxRenderer.h"
#include "YolonaOss/OpenGL/Window.h"
#include "SuthanusPhysicsLib/PhysicEngine.h"
#include "SuthanusPhysicsLib/Vehicle.h"
#include <IyathuumCoreLib/lib/glm/gtc/matrix_transform.hpp>
#include "IyathuumCoreLib/lib/glm/gtc/type_ptr.hpp"
#include <IyathuumCoreLib/lib/glm/gtx/quaternion.hpp>
#include "TankTower.h"
#include "Tank.h"
#include "Context.h"
#include "SuthanusPhysicsLib/ArtilleryAim.h"


namespace Fatboy
{
  Protagonist::Protagonist(std::shared_ptr<Context> context)
  {
    _context = context;
  }

  void Protagonist::load(YolonaOss::GL::DrawSpecification* spec)
  {
    _spec = spec;
    _tank = std::make_shared<Tank>(_context);
    _tank->load(spec);
  }

  void Protagonist::draw()
  {
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
    bool hit = _context->physic()->raycast(camPos, pickDir, hitPoint);
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
      _tank->fire();
      _pressed = true;
    }
    else if (!isPressed(YolonaOss::GL::Key::KEY_SPACE))
      _pressed = false;
    if (isPressed(YolonaOss::GL::Key::KEY_ENTER))
    {
      _tank = std::make_shared<Tank>(_context);
      _tank->load(_spec);
    }
  }

  glm::vec3 Protagonist::getPosition()
  {
    return _tank->getPosition();
  }

}