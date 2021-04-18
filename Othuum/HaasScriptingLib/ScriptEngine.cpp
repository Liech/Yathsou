#include "ScriptEngine.h"

#include <stdexcept>
#include <sstream>
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

    //https://stackoverflow.com/questions/4551101/lual-openlibs-and-sandboxing-scripts
    //luaL_requiref(_state, "_G", luaopen_base, 1);
    //lua_pop(_state, 1);

  }

  ScriptEngine::~ScriptEngine()
  {
    lua_close(_state);
  }
  
  void ScriptEngine::executeFile(const std::string& filename)
  {
    if (luaL_loadfile(_state, filename.c_str()) == LUA_OK) {
      int returnCode = lua_pcall(_state, 0, LUA_MULTRET, 0);
      if (returnCode != LUA_OK) {
        std::cout << lua_tostring(_state, -1) << std::endl;
        throw std::runtime_error("Error in call");
      }
    }
    else {
      std::cout << lua_tostring(_state, -1)<<std::endl;
      throw std::runtime_error("File not found");
    }
  }

  void ScriptEngine::executeString(const std::string& str) {
    int returnCode = luaL_dostring(_state, str.c_str());    
    if (returnCode != LUA_OK) {
      std::string lined = "";
      std::string current = "";
      std::istringstream f(str);
      size_t lineNo = 0;
      while (std::getline(f, current, '\n')) {
        lined += std::to_string(lineNo) + " " + current + "\n";
        lineNo++;
      }
      
      std::cout << lined << std::endl;
      std::cout << lua_tostring(_state, -1) << std::endl;
      throw std::runtime_error("Error in call");
    }
  }

  void ScriptEngine::registerFunction(const std::string& name, std::shared_ptr<std::function<nlohmann::json(const nlohmann::json&)>> call)
  {
    //https://stackoverflow.com/questions/61071267/how-to-reference-this-in-a-lambda-used-with-a-lua-script
    _registry.push_back(call);
    int regpos = _registry.size() - 1;
   
    auto callFunction = [](lua_State* L) -> int
    {
      ScriptEngine* This = (ScriptEngine*)lua_topointer(L, lua_upvalueindex(1));
      int pos = (int)lua_topointer(L, lua_upvalueindex(2));
      
      nlohmann::json input;
      nlohmann::json output;
      This->toJson(input);
      output = (*This->_registry[pos].get())(input);
      This->toTable(output);

      return 0;
    };
    
    lua_pushlightuserdata(_state, this);
    lua_pushlightuserdata(_state, (void*)regpos);
    lua_pushcclosure(_state, callFunction, 2);
    lua_setglobal(_state,name.c_str() );

  }

  nlohmann::json ScriptEngine::callScript(const std::string& name, const nlohmann::json& input)
  {
    nlohmann::json result;
    lua_getglobal(_state, name.c_str());
    toTable(input);
    int returnCode = lua_pcall(_state, 1,1,0);
    if (returnCode != LUA_OK) {
      //dumpGlobalVariables(true);
      std::cout << lua_tostring(_state, -1) << std::endl;
      throw std::runtime_error("script call error");
    }
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

  void ScriptEngine::dumpGlobalVariables(bool fullPrint)
  {
    lua_pushglobaltable(_state);       // Get global table
    lua_pushnil(_state);               // put a nil key on stack
    while (lua_next(_state, -2) != 0) { // key(-1) is replaced by the next key(-1) in table(-2)
      std::cout<<lua_tostring(_state, -2)<<std::endl;  // Get key(-2) name
      if (fullPrint)
        printTop(1);
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
          target[((int)nr)-1] = value; //array assignment
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
      int count = 1;
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
    toTable(value);
    lua_setglobal(_state, name.c_str());
  }

  nlohmann::json ScriptEngine::getVar(const std::string& name)
  {
    lua_getglobal(_state, name.c_str());
    nlohmann::json result;
    toJson(result);
    lua_pop(_state, 1);
    return result;
  }

  std::string ScriptEngine::cleanComments(const std::string& code, char symbol){
    std::string result = "";
    std::string current = "";
    std::istringstream f(code);
    size_t lineNo = 0;
    bool stringOpen = false;
    while (std::getline(f, current, '\n')) {
      int i = 0;
      for (; i < current.size(); i++) {
        if (current[i] == '"') {
          stringOpen = !stringOpen;
        }
        if (!stringOpen && current[i] == symbol) {
          break;
        }
      }
      result = result + current.substr(0,i) + "\n";
    }
    return result;
  }

}