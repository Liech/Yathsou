#include "Context.h"

#include "HaasScriptingLib/ScriptEngine.h"
#include "SuthanusPhysicsLib/PhysicEngine.h"
#include "BulletPool.h"
#include "UnitPool.h"

namespace Fatboy
{
  Context::Context()
  {
    _script  = std::make_shared<Haas::ScriptEngine    >();
    _physic  = std::make_shared<Suthanus::PhysicEngine>();
    _bullets = std::make_shared<BulletPool            >();
    _units   = std::make_shared<UnitPool              >();
  }

  std::shared_ptr<Haas::ScriptEngine> Context::script()
  {
    return _script;
  }

  std::shared_ptr<Suthanus::PhysicEngine> Context::physic()
  {
    return _physic;
  }

  std::shared_ptr<BulletPool> Context::bullets()
  {
    return _bullets;
  }

  std::shared_ptr<UnitPool> Context::units()
  {
    return _units;
  }
}