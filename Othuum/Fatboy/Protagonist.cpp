#include "Protagonist.h"

#include "YolonaOss/Renderer/BoxRenderer.h"
#include "YolonaOss/OpenGL/Window.h"
#include "SuthanusPhysicsLib/PhysicEngine.h"
#include "SuthanusPhysicsLib/Vehicle.h"
#include <IyathuumCoreLib/lib/glm/gtc/matrix_transform.hpp>
#include "IyathuumCoreLib/lib/glm/gtc/type_ptr.hpp"
#include <IyathuumCoreLib/lib/glm/gtx/quaternion.hpp>
#include "IyathuumCoreLib/Singleton/Database.h"
#include "TankTower.h"
#include "Unit.h"
#include "Context.h"
#include "UnitPool.h"
#include "SuthanusPhysicsLib/ArtilleryAim.h"


namespace Fatboy
{
  Protagonist::Protagonist(std::shared_ptr<Context> context, bool* drawDebug, std::shared_ptr < YolonaOss::Camera::CameraSystem> cam)
    :_drawDebug(drawDebug),
    _cam(cam)
  {
    _context = context;
  }

  void Protagonist::load(YolonaOss::GL::DrawSpecification* spec)
  {
    _spec = spec;
    _tank = std::make_shared<Unit>(_context);
    _tank->load(spec);
    _context->units()->addUnit(_tank);
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
    auto isPressed = [this](Iyathuum::Key key) {
      return _spec->getWindow()->getKeyStatus(key) == Iyathuum::KeyStatus::PRESS;
    };
    if (isPressed(Iyathuum::Key::KEY_W))
    {
      _tank->setAcceleration(_tank->maxAcceleration());
    }
    else if (isPressed(Iyathuum::Key::KEY_S))
    {
      _tank->setAcceleration(-_tank->maxAcceleration());
    }
    else
      _tank->setAcceleration(0);
    if (isPressed(Iyathuum::Key::KEY_A))
    {
      _tank->setSteering(_tank->maxSteering());
    }
    else if (isPressed(Iyathuum::Key::KEY_D))
    {
      _tank->setSteering(-_tank->maxSteering());
    }
    else
      _tank->setSteering(0);
    if (isPressed(Iyathuum::Key::KEY_SPACE) && !_pressed)
    {
      _tank->fire();
      _pressed = true;
    }
    else if (isPressed(Iyathuum::Key::KEY_F1) && !_pressed)
    {
      *_drawDebug = !*_drawDebug;
      _pressed = true;
    }
    else if (isPressed(Iyathuum::Key::KEY_F2) && !_pressed)
    {
      if (_cam->getCurrentCam() == "FollowCamera")
        _cam->setCurrentCam("FreeCamera");
      else
        _cam->setCurrentCam("FollowCamera");
      _pressed = true;
    }
    else if (!(isPressed(Iyathuum::Key::KEY_SPACE) || isPressed(Iyathuum::Key::KEY_F1) || isPressed(Iyathuum::Key::KEY_F2)))
      _pressed = false;
    if (isPressed(Iyathuum::Key::KEY_ENTER))
    {
      glm::vec2 pos = _spec->getWindow()->getCursorPos();
      glm::vec3 camPos = _spec->getCam()->getPosition();
      glm::vec3 pickDir = _spec->getCam()->getPickRay((float)pos.x, (float)pos.y);
      glm::vec3 hitPoint;
      Suthanus::PhysicObject* obj = _context->physic()->raycast(camPos, pickDir, hitPoint);
      std::shared_ptr<Suthanus::PhysicObject> lock;
      std::weak_ptr<Unit> cast;
      bool changed = false;
      if (obj && (lock = obj->self().lock()))
      {
        auto unitt = _context->units()->physicBodyToUnit(lock);
        if (unitt) {
          _tank = unitt;
          changed = true;
        }
      }
      
      if (!changed)
      {
        _context->units()->removeUnit(_tank);
        _tank = std::make_shared<Unit>(_context);
        _tank->load(_spec);
        _context->units()->addUnit(_tank);
      }
    }
  }

  glm::vec3 Protagonist::getPosition()
  {
    return _tank->getPosition();
  }

}