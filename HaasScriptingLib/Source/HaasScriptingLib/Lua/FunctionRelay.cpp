#include "FunctionRelay.h"

#include <lua.hpp>

namespace Haas {
  namespace Lua {
    FunctionRelay::FunctionRelay(lua_State* state) {
      _state = state;
    }

    nlohmann::json FunctionRelay::call(size_t id, const nlohmann::json&) {
      return nlohmann::json();
    }

    size_t FunctionRelay::addFunction() {
      return 0;
    }
  }
}