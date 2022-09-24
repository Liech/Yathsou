#include "FunctionRelay.h"

#include <lua.hpp>
#include <iostream>

#include "Conversion.h"

namespace Haas {
  namespace Lua {
    FunctionRelay::FunctionRelay(lua_State* state) {
      _state = state;

      lua_pushinteger(_state, 1);
      lua_setglobal(_state, "functionRelayCount");
      lua_createtable(_state, 0, 10);
      lua_setglobal(_state, "functionRelay");
    }

    nlohmann::json FunctionRelay::call(size_t id, const nlohmann::json& parameter) {
      lua_getglobal(_state, "functionRelay");
      lua_pushstring(_state, ("x" + std::to_string(id)).c_str());
      lua_gettable(_state, -2);
      Conversion c(_state, *this);
      c.toTable(parameter);
      lua_call(_state, 1, 1);
      nlohmann::json result;
      c.toJson(result);
      lua_pop(_state,2);
      return result;
    }

    size_t FunctionRelay::addFunction() {
      //Input Stack: VALUE
    
      lua_getglobal(_state, "functionRelayCount"); //Stack: VALUE,KEY
      int count = lua_tointeger(_state, -1);
      lua_pop(_state, 1);
      std::string s = "x" + std::to_string(count);
      lua_pushstring(_state, s.c_str());
      lua_insert(_state, -2); //Stack: KEY,VALUE
      
      lua_getglobal(_state, "functionRelay"); //Stack: KEY,VALUE,TABLE
      lua_insert(_state, -3); //Stack: TABLE,KEY,VALUE
      lua_settable(_state, -3);//TABLE[KEY] = VALUE
      lua_setglobal(_state, "functionRelay");
      
      lua_pushinteger(_state,count+1);
      lua_setglobal(_state, "functionRelayCount");

      lua_pushinteger(_state, count);

      return count;
    }
  }
}