#pragma once

#include <string>
#include <functional>
#include <set>
#include <memory>
#include "lib/json_fwd.hpp"
struct lua_State;

namespace Haas
{
  class ScriptEngine
  {
  public:
    ScriptEngine();
    ~ScriptEngine();

    void           executeFile     (const std::string& filename                         );
    nlohmann::json callScript      (const std::string& name, const nlohmann::json& input);
    nlohmann::json getVar          (const std::string& name                             );
    void           setVar          (const std::string& name, const nlohmann::json& value);
    void           registerFunction(const std::string& name, std::shared_ptr < std::function < nlohmann::json(const nlohmann::json&)>>);
  private:
    void dumpStack();
    void printTop(int indentation = 0);
    void dumpGlobalVariables(bool fullPrint);

    void        toTable(const nlohmann::json& json);//debug
    void        toJson (nlohmann::json& json);      //debug
    std::string popStr (int pos);                   //debug

    std::vector<std::shared_ptr<std::function < nlohmann::json(const nlohmann::json&)>>> _registry;
    lua_State*                                                                        _state   ;
  };
}