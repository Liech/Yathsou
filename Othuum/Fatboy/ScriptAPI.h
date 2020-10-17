#pragma once

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
  class ScriptAPI
  {
  public:
    ScriptAPI(Suthanus::PhysicEngine*);
    void registerAPI(Haas::ScriptEngine*);
  private:
    Suthanus::PhysicEngine* _physic;
  };
}