#pragma once

#include <string>
#include <functional>
#include <set>
#include <memory>
struct lua_State;

namespace Haas
{
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

    void registerAverage();
    void registerFunction(std::string name, std::shared_ptr < std::function < void(ScriptEngineAPI*)>>);
  private:
    std::set<std::shared_ptr<std::function<void(ScriptEngineAPI*)>>> _registry;
    lua_State*       _state;
    ScriptEngineAPI* _api;
  };

}