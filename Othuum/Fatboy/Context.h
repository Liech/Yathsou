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
  class UnitPool;

  //semi "Singleton", which contains stuff that exists only once per timestep
  class Context
  {
  public:
    Context();
    std::shared_ptr<Haas::ScriptEngine    > script();
    std::shared_ptr<Suthanus::PhysicEngine> physic();
    std::shared_ptr<BulletPool>             bullets();
    std::shared_ptr<UnitPool>               units();
  private:   
    std::shared_ptr<Haas::ScriptEngine    > _script;
    std::shared_ptr<Suthanus::PhysicEngine> _physic;
    std::shared_ptr<BulletPool>             _bullets;
    std::shared_ptr<UnitPool>               _units;
  };
}