#pragma once

#include <memory>

namespace Haas
{
  class ScriptEngine;
}
namespace Suthanus
{
  class PhysicEngine;
}

namespace Fatboy
{
  class BulletPool;

  //semi "Singleton", which contains stuff that exists only once per timestep
  class Context
  {
  public:
    Context();
    std::shared_ptr<Haas::ScriptEngine    > script();
    std::shared_ptr<Suthanus::PhysicEngine> physic();
    std::shared_ptr<BulletPool>             bullets();
  private:
    std::shared_ptr<Haas::ScriptEngine    > _script;
    std::shared_ptr<Suthanus::PhysicEngine> _physic;
    std::shared_ptr<BulletPool>             _bullets;
  };
}