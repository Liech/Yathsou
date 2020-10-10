#include "ScriptEngine.h"

#include "lua.hpp"

void ScriptEngine::blubb()
{
  lua_State* L = luaL_newstate();

  // Load the libraries
  luaL_openlibs(L);

  // Execution of a lua string
  luaL_dostring(L, "print \"Yo dude\"");

  // Load a string and then execute it.
  luaL_loadstring(L, "io.write(\"I'm here too\\n\")");
  lua_pcall(L, 0, LUA_MULTRET, 0);

  // Load from a file and then execute
  if (luaL_loadfile(L, "test/hello.lua") == 0) {
    // File loaded call it
    lua_pcall(L, 0, LUA_MULTRET, 0);
  }

  // Close lua
  lua_close(L);

}