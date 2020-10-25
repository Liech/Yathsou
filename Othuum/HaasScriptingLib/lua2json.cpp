#include "lua2json.h"

#include "ScriptEngine.h"
#include <iostream>
namespace Haas
{
  nlohmann::json lua2json::fromLua(std::string filename)
  {
    ScriptEngine engine;
    engine.executeFile(filename);
    for (int i = 0; i < engine.api()->getStackCount(); i++)
    {
      std::cout << i << std::endl;
    }

    return nlohmann::json();
  }

}