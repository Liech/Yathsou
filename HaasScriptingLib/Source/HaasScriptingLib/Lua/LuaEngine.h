#pragma once

#include <string>
#include <functional>
#include <set>
#include <memory>
#include <nlohmann/json_fwd.hpp>

namespace Iyathuum {
  class API;
  class FunctionRelay;
}

struct lua_State;

namespace Haas {
  namespace Lua {
    class FunctionRelay;
    class Conversion;

    class LuaEngine {
      public:
      LuaEngine();
      LuaEngine(std::vector<std::unique_ptr<Iyathuum::API>>&);
      ~LuaEngine();

      static std::string cleanComments(const std::string& code, char symbol = '#'); //supreme commander bp files uses this unauthorized comment

      void           executeFile     (const std::string& filename);
      void           executeString   (const std::string& str);
      nlohmann::json callScript      (const std::string& name, const nlohmann::json& input);
      nlohmann::json getVar          (const std::string& name);
      void           setVar          (const std::string& name, const nlohmann::json& value);
      void           registerFunction(const std::string& name, std::function < nlohmann::json(const nlohmann::json&)>);

      Iyathuum::FunctionRelay& getRelay();
    private:
      void initialize();
      void printTop(int indentation = 0);
      void dumpGlobalVariables(bool fullPrint);

      std::unique_ptr<Lua::FunctionRelay>         _relay;
      std::vector<std::unique_ptr<Iyathuum::API>> _apis;

      class pimpl; //for handing over in registerFunction
      std::unique_ptr<pimpl> _pimpl; 
    };
  }
}