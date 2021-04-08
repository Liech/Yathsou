#include "ScriptAPI.h"

namespace Fatboy
{
  ScriptAPI::ScriptAPI(Suthanus::PhysicEngine* engine)
  {
    _physic = engine;
  }
  
  void ScriptAPI::registerAPI(Haas::ScriptEngine*)
  {

  }
}