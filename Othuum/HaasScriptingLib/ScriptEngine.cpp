#include "ScriptEngine.h"

#include <stdexcept>
#include "lua.hpp"
#include "lstate.h"
#include "IyathuumCoreLib/Util/lambdaCapture2functionPointer.h"

namespace Haas
{
  ScriptEngine::ScriptEngine()
  {
    _state = luaL_newstate();
    _api = new ScriptEngineAPI(_state);
    luaL_openlibs(_state);
    _state->___scriptEngine = _api;
  }

  ScriptEngine::~ScriptEngine()
  {
    lua_close(_state);
    delete _api;
  }

  void ScriptEngine::blubb()
  {

    // Execution of a lua string
    luaL_dostring(_state, "print \"Yo dude\"");

    // Load a string and then execute it.
    luaL_loadstring(_state, "io.write(\"I'm here too\\n\")");
    lua_pcall(_state, 0, LUA_MULTRET, 0);

    // Load from a file and then execute
    if (luaL_loadfile(_state, "test/hello.lua") == 0) {
      // File loaded call it
      lua_pcall(_state, 0, LUA_MULTRET, 0);
    }

    executeFile("add.lua");
  }

  void ScriptEngine::executeFile(std::string filename)
  {
    if (luaL_loadfile(_state, filename.c_str()) == 0) {
      lua_pcall(_state, 0, LUA_MULTRET, 0);
    }
    else
      throw std::runtime_error("File not found");
  }

  int ScriptEngine::callAdd(std::string name, int a, int b)
  {
    int sum;
    lua_getglobal(_state, name.c_str());
    _api->resetNumberOfPushes();
    _api->pushNumber(a);
    _api->pushNumber(b);
    lua_call(_state, _api->numberOfPushes(), 1);
    sum = _api->getStackElementAsInt(-1);
    lua_pop(_state, 1);
    _api->resetNumberOfPushes();
    return sum;
  }

  void ScriptEngine::registerAverage()
  {    
    std::shared_ptr<std::function<void(ScriptEngineAPI*)>> p = std::make_shared<std::function<void(ScriptEngineAPI*)>>([](ScriptEngineAPI* api) {
      int n = api->getStackCount();
      double sum = 0;
      int i;
      for (i = 1; i <= n; i++)
      {
        /* total the arguments */
        sum += api->getStackElementAsInt(i);
      }
      api->pushNumber(sum / n);
      api->pushNumber(sum);
    });
    registerFunction("average", p);
    luaL_dofile(_state, "average.lua");
  }

  void ScriptEngine::registerFunction(std::string name, std::shared_ptr<std::function<void(ScriptEngineAPI*)>> call)
  {
    _registry.insert(call);
    auto fn = Iyathuum::lambdaCapture2functionPointer<int(lua_State*)>([&](lua_State* state)
      {
        auto api = (ScriptEngineAPI*)state->___scriptEngine;
        api->resetNumberOfPushes();
        (*call.get())(api);
        return api->numberOfPushes();
      });
    lua_register(_state, name.c_str(), fn);
  }

  std::vector<any> ScriptEngine::callScript(std::string name, std::vector<any> inputArgs, std::vector<any::type> outputTypes)
  {
    lua_getglobal(_state, name.c_str());
    _api->resetNumberOfPushes();
    for (int i = 0; i < inputArgs.size(); i++)
    {
      switch (inputArgs[i].get_type()) {
      case any::type::Int:
        _api->pushNumber(inputArgs[i].get_int());
        break;
      case any::type::Float:
        _api->pushNumber(inputArgs[i].get_float());
        break;
      case any::type::String:
        throw std::runtime_error("not implemented");
        break;
      }
    }
    lua_call(_state, _api->numberOfPushes(), outputTypes.size());
    std::vector<any> result;
    for (int i = 0; i < outputTypes.size(); i++)
    {
      switch (outputTypes[i]) {
      case any::type::Int:
        result.push_back(_api->getStackElementAsInt(-((int)outputTypes.size()) + i));
        break;
      case any::type::Float:
        throw std::runtime_error("not implemented");
        break;
      case any::type::String:
        throw std::runtime_error("not implemented");
        break;
      }
    }
    lua_pop(_state, (int)outputTypes.size());
    _api->resetNumberOfPushes();
    return result;
  }

  ScriptEngineAPI::ScriptEngineAPI(lua_State* state)
  {
    _state = state;
  }

  int ScriptEngineAPI::getStackCount()
  {
    return lua_gettop(_state);
  }

  int ScriptEngineAPI::getStackElementAsInt(int number)
  {
    return lua_tointeger(_state, number);
  }

  double ScriptEngineAPI::getStackElementAsDouble(int number)
  {
    return lua_tonumber(_state, number);
  }

  void ScriptEngineAPI::pushNumber(int number)
  {
    lua_pushnumber(_state, number);
    _numberOfPushes++;
  }

  void ScriptEngineAPI::resetNumberOfPushes()
  {
    _numberOfPushes = 0;
  }

  int ScriptEngineAPI::numberOfPushes()
  {
    return _numberOfPushes;
  }
}