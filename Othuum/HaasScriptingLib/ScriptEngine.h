#pragma once

#include <string>
#include <functional>
#include <set>
#include <memory>
#include "lib/json.hpp"
struct lua_State;

namespace Haas
{
  struct any {
    enum class type { Int, Float, String };
    any(int   e) { m_data.INT = e; m_type = any::type::Int; }
    any(float e) { m_data.FLOAT = e; m_type = any::type::Float; }
    any(char* e) { m_data.STRING = e; m_type = any::type::String; }
    type get_type() const { return m_type; }
    int get_int() const { return m_data.INT; }
    float get_float() const { return m_data.FLOAT; }
    char* get_string() const { return m_data.STRING; }
  private:
    type m_type;
    union {
      int   INT;
      float FLOAT;
      char* STRING;
    } m_data;
  };

  class ScriptEngineAPI
  {
  public:
    ScriptEngineAPI(lua_State*);
    int  getStackCount();
    int  getStackElementAsInt(int number);
    double  getStackElementAsDouble(int number);
    void pushNumber(int number);
    void resetNumberOfPushes();
    int  numberOfPushes();

  private:
    lua_State* _state;
    int        _numberOfPushes = 0;
  };

  class ScriptEngine
  {
  public:
    ScriptEngine();
    ~ScriptEngine();
    void blubb();

    void executeFile(std::string filename);
    int callAdd(std::string name, int a, int b);
    ScriptEngineAPI* api() {
      return _api;
    };
    void dumpStack();
    void dumpGlobalVariables();

    std::vector<any> callScript(std::string name, std::vector<any>, std::vector<any::type> outputTypes = {});
    nlohmann::json getVar(std::string name);
    void           setVar(std::string name, nlohmann::json value);
    void registerAverage();
    void registerFunction(std::string name, std::shared_ptr < std::function < void(ScriptEngineAPI*)>>);
  private:
    void toTable(const nlohmann::json& json);
    void toJson(nlohmann::json& json);
    std::string popStr(int pos);
    void printTop(int indentation = 0);
    std::set<std::shared_ptr<std::function<void(ScriptEngineAPI*)>>> _registry;
    lua_State*       _state;
    ScriptEngineAPI* _api;
  };
}