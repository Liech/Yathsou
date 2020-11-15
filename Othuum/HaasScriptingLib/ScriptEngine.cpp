#include "ScriptEngine.h"

#include <stdexcept>
#include "lua.hpp"
#include "lstate.h"
#include "IyathuumCoreLib/Util/lambdaCapture2functionPointer.h"
#include <iostream>
#include "lib/json.hpp"

namespace Haas
{
  ScriptEngine::ScriptEngine()
  {
    _state = luaL_newstate();
    luaL_openlibs(_state);
  }

  ScriptEngine::~ScriptEngine()
  {
    lua_close(_state);
  }

  void ScriptEngine::executeFile(const std::string& filename)
  {
    if (luaL_loadfile(_state, filename.c_str()) == 0) {
      lua_pcall(_state, 0, LUA_MULTRET, 0);
    }
    else
      throw std::runtime_error("File not found");
  }

  void ScriptEngine::registerFunction(const std::string& name, std::shared_ptr<std::function<nlohmann::json(const nlohmann::json&)>> call)
  {
    _registry.insert(call);
    auto fn = Iyathuum::lambdaCapture2functionPointer<int(lua_State*)>([&](lua_State* state)
      {
        
        nlohmann::json input ;        
        nlohmann::json output;
        toJson(input);
        output = (*call.get())(input);
        toTable(output);
        return 1;
      });
    lua_register(_state, name.c_str(), fn);
  }

  nlohmann::json ScriptEngine::callScript(const std::string& name, const nlohmann::json& input)
  {
    nlohmann::json result;
    lua_getglobal(_state, name.c_str());
    toTable(input);
    lua_call(_state, 1,1);
    toJson(result);
    lua_pop(_state, 1);
    return result;
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
        float number = lua_tonumber(_state, -1);
        if (number == (int)number)
          result = (int)number;
        else
          result = number;
      }
      else if (lua_isboolean(_state, -1)) {
        result = lua_toboolean(_state, -1);
      }
      else
        throw std::runtime_error("Unkown type");
      return;
    }

    auto assign = [this](nlohmann::json& target, nlohmann::json value) {
      
      if (lua_isnumber(_state, -2)) {
        float nr = lua_tonumber(_state, -2);
        if (nr == (int)nr)
          target[(int)nr] = value;
        else
          target[nr] = value;
      }
      else if (lua_isstring(_state, -2)) {
        target[lua_tostring(_state, -2)] = value;
      }
    };

    lua_pushnil(_state);  /* first key */
    int amount = 0;
    while (lua_next(_state, -2) != 0) {
      if (lua_isnumber(_state, -1)) {
        float number = lua_tonumber(_state, -1);
        if (number == (int)number)
          assign(result, (int)number);
        else
          assign(result, number);
      }
      else if (lua_isboolean(_state, -1)) {
        assign(result, lua_toboolean(_state, -1));
      }
      else if (lua_isstring(_state, -1)) {
        assign(result, popStr(-1));
      }
      else if (lua_istable(_state, -1)) {
        nlohmann::json sub;
        toJson(sub);
        assign(result, sub);
      }
      else
        throw std::runtime_error("Unkown Type");
      lua_pop(_state, 1);
    }
  }

  void ScriptEngine::toTable(const nlohmann::json& value)
  {
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
    else if (value.type_name() == "binary")
    {
      throw std::runtime_error("Not implemented yet!");
    }
    else if (value.type_name() == "array")
    {
      lua_newtable(_state);
      int count = 0;
      for (auto item : value.items())
      {
        nlohmann::json value = item.value();
        lua_pushnumber(_state, count);
        toTable(value);
        lua_settable(_state, -3);
        count++;
      }
    }
    else if (value.type_name() == "object")
    {
      lua_newtable(_state);
      for (auto item : value.items())
      {
        std::string    key = item.key();
        nlohmann::json value = item.value();
        lua_pushstring(_state, key.c_str());
        toTable(value);
        lua_settable(_state, -3);
      }
    }
  }

  void ScriptEngine::setVar(const std::string& name, const nlohmann::json& value) {
    std::cout << "t1" << std::endl;
    dumpStack();
    std::cout << "ASD" << value.dump(4) << std::endl;
    std::cout << "t2" << std::endl;
    dumpStack();
    toTable(value);
    printTop();
    lua_setglobal(_state, name.c_str());
  }

  nlohmann::json ScriptEngine::getVar(const std::string& name)
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