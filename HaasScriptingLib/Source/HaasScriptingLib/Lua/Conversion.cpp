#include "Conversion.h"

#include <lua.hpp>

namespace Haas {
  namespace Lua {
    Conversion::Conversion(lua_State* state, Lua::FunctionRelay& relay) 
      : _relay(relay) { 
      _state = state;
    }


    void Conversion::toJson(nlohmann::json& result) {
      std::string indent = "";
      int top = lua_gettop(_state);
      if (top == 0)
        return;

      if (!lua_istable(_state, -1)) {
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
        else {
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
          throw std::runtime_error("Unkown type");
        }
        return;
      }

      auto assign = [this](nlohmann::json& target, nlohmann::json value) {

        if (lua_isnumber(_state, -2)) {
          float nr = lua_tonumber(_state, -2);
          if (nr == (int)nr)
            target[((int)nr) - 1] = value; //array assignment
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

    void Conversion::toTable(const nlohmann::json& value) {
      if (value.type_name() == "number") {
        if (value.is_number_float()) {
          float v = value;
          lua_pushnumber(_state, v);
        }
        else {
          int v = value;
          lua_pushnumber(_state, v);
        }
      }
      else if (value.type_name() == "boolean") {
        bool v = value;
        lua_pushboolean(_state, v);
      }
      else if (value.type_name() == "string") {
        std::string v = value;
        lua_pushstring(_state, v.c_str());
      }
      else if (value.type_name() == "binary") {
        throw std::runtime_error("Not implemented yet!");
      }
      else if (value.type_name() == "array") {
        lua_newtable(_state);
        int count = 1;
        for (auto item : value.items()) {
          nlohmann::json value = item.value();
          lua_pushnumber(_state, count);
          toTable(value);
          lua_settable(_state, -3);
          count++;
        }
      }
      else if (value.type_name() == "object") {
        lua_newtable(_state);
        for (auto item : value.items()) {
          std::string    key = item.key();
          nlohmann::json value = item.value();
          lua_pushstring(_state, key.c_str());
          toTable(value);
          lua_settable(_state, -3);
        }
      }
    }

    std::string Conversion::popStr(int pos) {
      if (lua_isnumber(_state, pos))
        return std::to_string(lua_tonumber(_state, pos));
      else if (lua_isstring(_state, pos))
        return lua_tostring(_state, pos);

      throw std::runtime_error("Unkown");
    }
  }
}