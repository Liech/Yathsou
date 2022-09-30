#include "LuaEngine.h"

#include <stdexcept>
#include <sstream>
#include <lua.hpp>
#include <iostream>
#include <nlohmann/json.hpp>

#include <IyathuumCoreLib/API/API.h>
#include <IyathuumCoreLib/API/APIFunction.h>

#include "Conversion.h"
#include "FunctionRelay.h"


namespace Haas {
  namespace Lua {
    class LuaEngine::pimpl {
      public:
      lua_State*                                                        _state     = nullptr;
      std::unique_ptr<Lua::Conversion>                                  _conversion;
      std::vector<std::function<nlohmann::json(const nlohmann::json&)>> _registry;      
      std::vector<std::unique_ptr<Iyathuum::API>> _apis;
    };


    LuaEngine::LuaEngine() {
      initialize();
    }

    void LuaEngine::addApi(std::unique_ptr<Iyathuum::API> api){
      int apiIndex = _pimpl->_apis.size();
      for (size_t i = 0; i < api->numberOfFunctions(); i++) {
        auto fun = api->getFunction(i);
        registerFunction(fun.getName(), [this, i,apiIndex](const nlohmann::json& input) {
          return _pimpl->_apis[apiIndex]->getFunction(i).call(input);
          });
      }
      _pimpl->_apis.push_back(std::move(api));
    }

    void LuaEngine::initialize() { 
      _pimpl = std::make_unique<Lua::LuaEngine::pimpl>();
      _pimpl->_state = luaL_newstate();
      _relay = std::make_unique<Lua::FunctionRelay>(_pimpl->_state);
      _pimpl->_conversion = std::make_unique<Lua::Conversion>(_pimpl->_state, *_relay);

      luaL_openlibs(_pimpl->_state);
    }

    LuaEngine::~LuaEngine() {
      lua_close(_pimpl->_state);
    }

    void LuaEngine::executeFile(const std::string& filename) {
      if (luaL_loadfile(_pimpl->_state, filename.c_str()) == LUA_OK) {
        int returnCode = lua_pcall(_pimpl->_state, 0, LUA_MULTRET, 0);
        if (returnCode != LUA_OK) {
          std::cout << lua_tostring(_pimpl->_state, -1) << std::endl;
          throw std::runtime_error("Error in call");
        }
      }
      else {
        std::cout << lua_tostring(_pimpl->_state, -1) << std::endl;
        throw std::runtime_error("File not found or Syntax Error");
      }
    }

    void LuaEngine::executeString(const std::string& str) {
      int returnCode = luaL_dostring(_pimpl->_state, str.c_str());
      if (returnCode != LUA_OK) {
        std::string lined = "";
        std::string current = "";
        std::istringstream f(str);
        size_t lineNo = 0;
        while (std::getline(f, current, '\n')) {
          lined += std::to_string(lineNo) + " " + current + "\n";
          lineNo++;
        }

        std::cout << lined << std::endl;
        std::cout << lua_tostring(_pimpl->_state, -1) << std::endl;
        throw std::runtime_error("Error in call");
      }
    }

    void LuaEngine::registerFunction(const std::string& name, std::function<nlohmann::json(const nlohmann::json&)> call) {
      //https://stackoverflow.com/questions/61071267/how-to-reference-this-in-a-lambda-used-with-a-lua-script
      _pimpl->_registry.push_back(call);

      int regpos = _pimpl->_registry.size() - 1;

      auto callFunction = [](lua_State* L) -> int {
        LuaEngine::pimpl* This = (LuaEngine::pimpl*)lua_topointer(L, lua_upvalueindex(1));
        int pos = (int)lua_topointer(L, lua_upvalueindex(2));

        nlohmann::json input;
        nlohmann::json output;

        This->_conversion->toJson(input);
        output = This->_registry[pos](input);
        This->_conversion->toTable(output);
        return 1;
      };

      lua_pushlightuserdata(_pimpl->_state, &(*_pimpl));
      lua_pushlightuserdata(_pimpl->_state, (void*)regpos);
      lua_pushcclosure(_pimpl->_state, callFunction, 2);
      lua_setglobal(_pimpl->_state, name.c_str());
    }

    nlohmann::json LuaEngine::callScript(const std::string& name, const nlohmann::json& input) {
      nlohmann::json result;
      lua_getglobal(_pimpl->_state, name.c_str());
      _pimpl->_conversion->toTable(input);
      int returnCode = lua_pcall(_pimpl->_state, 1, 1, 0);
      if (returnCode != LUA_OK) {
        //dumpGlobalVariables(true);
        std::cout << lua_tostring(_pimpl->_state, -1) << std::endl;
        throw std::runtime_error("script call error");
      }
      _pimpl->_conversion->toJson(result);
      lua_pop(_pimpl->_state, 1);
      return result;
    }

    void LuaEngine::dumpGlobalVariables(bool fullPrint) {
      lua_pushglobaltable(_pimpl->_state);       // Get global table
      lua_pushnil(_pimpl->_state);               // put a nil key on stack
      while (lua_next(_pimpl->_state, -2) != 0) { // key(-1) is replaced by the next key(-1) in table(-2)
        std::cout << lua_tostring(_pimpl->_state, -2) << std::endl;  // Get key(-2) name
        if (fullPrint)
          printTop(1);
        lua_pop(_pimpl->_state, 1);               // remove value(-1), now key on top at(-1)
      }
      lua_pop(_pimpl->_state, 1);                 // remove global table(-1)
    }

    void LuaEngine::printTop(int indentation) {
      std::string indent = "";
      for (int i = 0; i < indentation; i++)
        indent += " ";

      if (!lua_istable(_pimpl->_state, -1)) {
        if (lua_isstring(_pimpl->_state, -1)) {
          std::cout << indent << _pimpl->_conversion->popStr(-1) << std::endl;
        }
        else if (lua_isnumber(_pimpl->_state, -1)) {
          std::cout << indent << lua_tonumber(_pimpl->_state, -1) << std::endl;
        }
        else if (lua_isboolean(_pimpl->_state, -1)) {
          std::cout << indent << lua_toboolean(_pimpl->_state, -1) << std::endl;
        }
        else
          std::cout << indent << "UNKOWN" << std::endl;
        return;
      }

      lua_pushnil(_pimpl->_state);  /* first key */
      int amount = 0;
      while (lua_next(_pimpl->_state, -2) != 0) {
        if (lua_isstring(_pimpl->_state, -1)) {
          std::cout << indent << _pimpl->_conversion->popStr(-2) << ": " << _pimpl->_conversion->popStr(-1) << std::endl;
        }
        else if (lua_isnumber(_pimpl->_state, -1)) {
          std::cout << indent << _pimpl->_conversion->popStr(-2) << ": " << lua_tonumber(_pimpl->_state, -1) << std::endl;
        }
        else if (lua_isboolean(_pimpl->_state, -1)) {
          std::cout << indent << _pimpl->_conversion->popStr(-2) << ": " << lua_toboolean(_pimpl->_state, -1) << std::endl;
        }
        else if (lua_istable(_pimpl->_state, -1)) {
          printTop(indentation + 1);
        }
        else
          std::cout << indent << "UNKOWN" << std::endl;
        lua_pop(_pimpl->_state, 1);
      }
    }

    void LuaEngine::setVar(const std::string& name, const nlohmann::json& value) {
      _pimpl->_conversion->toTable(value);
      lua_setglobal(_pimpl->_state, name.c_str());
    }

    nlohmann::json LuaEngine::getVar(const std::string& name) {
      lua_getglobal(_pimpl->_state, name.c_str());
      nlohmann::json result;
      _pimpl->_conversion->toJson(result);
      lua_pop(_pimpl->_state, 1);
      return result;
    }

    std::string LuaEngine::cleanComments(const std::string& code, char symbol) {
      std::string result = "";
      std::string current = "";
      std::istringstream f(code);
      size_t lineNo = 0;
      bool stringOpen = false;
      while (std::getline(f, current, '\n')) {
        int i = 0;
        for (; i < current.size(); i++) {
          if (current[i] == '"' || current[i] == '\'') {
            stringOpen = !stringOpen;
          }
          if (!stringOpen && current[i] == symbol) {
            break;
          }
        }
        result = result + current.substr(0, i) + "\n";
      }
      return result;
    }

    Iyathuum::FunctionRelay& LuaEngine::getRelay() {
      return *_relay;
    }
  }
}