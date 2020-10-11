#pragma once

#include <string>
struct lua_State;

namespace Haas
{
  class ScriptEngine
  {
  public:
    void blubb();

    void executeFile(std::string filename);

  private:
    lua_State* _state;
  };
}