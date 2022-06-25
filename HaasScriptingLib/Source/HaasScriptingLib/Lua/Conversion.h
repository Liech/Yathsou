#pragma once

#include <nlohmann/json.hpp>

struct lua_State;

namespace Haas {
  namespace Lua {
    class FunctionRelay;

    class Conversion {
      public:
      Conversion(lua_State*, Lua::FunctionRelay&);

      void toTable(const nlohmann::json& json);
      void toJson(nlohmann::json& json);
      std::string popStr(int pos);

      private:

      Lua::FunctionRelay& _relay;
      lua_State*          _state;
    };
  }
}