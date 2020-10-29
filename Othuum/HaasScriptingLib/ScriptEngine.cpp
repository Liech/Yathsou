#include "ScriptEngine.h"

#include <stdexcept>
#include "lua.hpp"
#include "lstate.h"
#include "IyathuumCoreLib/Util/lambdaCapture2functionPointer.h"
#include <iostream>

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


  void ScriptEngine::dumpStack()
  {
    int top = lua_gettop(_state);
    //printf("(%s,%d) top=%d\n", func, line, top);
    for (int i = 0; i < top; i++) {
      int positive = top - i;
      int negative = -(i + 1);
      int type = lua_type(_state, positive);
      int typeN = lua_type(_state, negative);
      const char* typeName = lua_typename(_state, type);
      printf("%d/%d: type=%s", positive, negative, typeName);
      switch (type) {
      case LUA_TNUMBER:
        printf(" value=%f", lua_tonumber(_state, positive));
        break;
      case LUA_TSTRING:
        printf(" value=%s", lua_tostring(_state, positive));
        break;
      case LUA_TFUNCTION:
        if (lua_iscfunction(_state, positive)) {
          printf(" C:%p", lua_tocfunction(_state, positive));
        }
        break;
      }
      printf("\n");
    }
  }

  void ScriptEngine::dumpGlobalVariables()
  {
    lua_pushglobaltable(_state);       // Get global table
    lua_pushnil(_state);               // put a nil key on stack
    while (lua_next(_state, -2) != 0) { // key(-1) is replaced by the next key(-1) in table(-2)
      std::cout<<lua_tostring(_state, -2)<<std::endl;  // Get key(-2) name
      lua_pop(_state, 1);               // remove value(-1), now key on top at(-1)
    }
    lua_pop(_state, 1);                 // remove global table(-1)
  }

  std::string ScriptEngine::popStr(int pos)
  {
    if (lua_isnumber(_state, pos))
      return std::to_string(lua_tonumber(_state, pos));
    else if (lua_isstring(_state, pos))
      return lua_tostring(_state, pos);
     
    throw std::runtime_error("Unkown");
  }

  void ScriptEngine::printTop(int indentation)
  {
    std::string indent = "";
    for (int i = 0; i < indentation; i++)
      indent += " ";

    if (!lua_istable(_state, -1))
    {
      if (lua_isstring(_state, -1)) {
        std::cout << indent << popStr(-1) << std::endl;
      }
      else if (lua_isnumber(_state, -1)) {
        std::cout << indent << lua_tonumber(_state, -1) << std::endl;
      }
      else if (lua_isboolean(_state, -1)) {
        std::cout << indent << lua_toboolean(_state, -1) << std::endl;
      }
      else
        std::cout << indent << "UNKOWN" << std::endl;
      return;
    }

    lua_pushnil(_state);  /* first key */
   int amount = 0;
   while (lua_next(_state, -2) != 0) {
      if (lua_isstring(_state, -1)) {
       std::cout << indent << popStr(-2) << ": " << popStr(-1) << std::endl;
      }
      else if (lua_isnumber(_state, -1)) {
       std::cout << indent << popStr(-2) << ": " << lua_tonumber(_state, -1) << std::endl;
      }
      else if (lua_isboolean(_state, -1)) {
       std::cout << indent << popStr(-2) << ": " << lua_toboolean(_state, -1) << std::endl;
      }
     else if (lua_istable(_state, -1)) {
       printTop(indentation + 1);
     }
     else
       std::cout << indent << "UNKOWN" << std::endl;
     lua_pop(_state, 1);
   }
  }

  void ScriptEngine::toJson(nlohmann::json& result)
  {
    std::string indent = "";

    if (!lua_istable(_state, -1))
    {
      if (lua_isstring(_state, -1)) {
        result = popStr(-1);
      }
      else if (lua_isnumber(_state, -1)) {
        result= lua_tonumber(_state, -1);
      }
      else if (lua_isboolean(_state, -1)) {
        result = lua_toboolean(_state, -1);
      }
      else
        throw std::runtime_error("Unkown type");
      return;
    }

    lua_pushnil(_state);  /* first key */
    int amount = 0;
    while (lua_next(_state, -2) != 0) {
      if (lua_isstring(_state, -1)) {
        result[popStr(-2)] = popStr(-1);
      }
      else if (lua_isnumber(_state, -1)) {
        result[popStr(-2)] = lua_tonumber(_state, -1);
      }
      else if (lua_isboolean(_state, -1)) {
        result[popStr(-2)] = lua_toboolean(_state, -1);
      }
      else if (lua_istable(_state, -1)) {
        nlohmann::json sub;
        toJson(sub);
        result[popStr(-2)] = sub;
      }
      else
        throw std::runtime_error("Unkown Type");
      lua_pop(_state, 1);
    }
  }
  void ScriptEngine::setVar(std::string name, nlohmann::json value) {
    std::cout << "t1" << std::endl;
    dumpStack();
    std::cout << "ASD" << value.dump(4) << std::endl;
    std::cout << "t2" << std::endl;
    dumpStack();

    for (auto item : value.items())
    {
      std::string    key   = item.key();
      nlohmann::json value = item.value();
      
      if (value.type_name() == "number")
      {
        if (value.is_number_float())
        {
          float v = value;
          lua_pushnumber(_state, v);
        }
        else
        {
          int v = value;
          lua_pushnumber(_state, v);
        }
      }
      else if (value.type_name() == "boolean")
      {
        bool v = value;
        lua_pushboolean(_state, v);
      }
      else if (value.type_name() == "string")
      {
        std::string v = value;
        lua_pushstring(_state, v.c_str());
      }
      else if (value.type_name() == "array")
      {
        throw std::runtime_error("Not implemented yet!");
      }
      else if (value.type_name() == "object")
      {
        lua_newtable(_state);
        lua_pushstring(_state, key.c_str());
        throw std::runtime_error("Deeper");
        lua_settable(_state, -3);
        throw std::runtime_error("Not implemented yet!");
      }
      else if (value.type_name() == "binary")
      {
        throw std::runtime_error("Not implemented yet!");
      }
      else throw std::runtime_error("Unkown type");
      std::cout << "while" << std::endl;
      dumpStack();
    }
    //print_table(0);
    lua_setglobal(_state, name.c_str());
  }

  nlohmann::json ScriptEngine::getVar(std::string name)
  {
    lua_getglobal(_state, name.c_str());
    printTop(0);
    nlohmann::json result;
    toJson(result);
    dumpStack();
    lua_pop(_state, 1);
    return result;
  }

}