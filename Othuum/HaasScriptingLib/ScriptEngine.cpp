#include "ScriptEngine.h"

#include <stdexcept>
#include "lua.hpp"

namespace Haas
{
  void ScriptEngine::blubb()
  {
    _state = luaL_newstate();
    luaL_openlibs(_state);

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

    // Close lua
    lua_close(_state);

  }

  void ScriptEngine::executeFile(std::string filename)
  {
    if (luaL_loadfile(_state, filename.c_str()) == 0) {
      lua_pcall(_state, 0, LUA_MULTRET, 0);
    }
    else
      throw std::runtime_error("File not found");
  }
}