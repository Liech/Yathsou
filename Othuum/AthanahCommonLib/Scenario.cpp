#include "Scenario.h"

#include <iostream>
#include <fstream>

#include "AezeselFileIOLib/lib/json.hpp"
#include "HaasScriptingLib/ScriptEngine.h"

namespace Athanah {
  Scenario::Scenario(const std::string& path) {
    _path = path;

    Haas::ScriptEngine script;
    std::shared_ptr<std::function<nlohmann::json(const nlohmann::json&)>> STRING = std::make_shared< std::function<nlohmann::json(const nlohmann::json&)>>(
      [&](const nlohmann::json& input) -> nlohmann::json
    {
      return 1;
    }
    );
    script.registerFunction("STRING", STRING);


    bool called = false;

    std::ifstream t(path);
    std::string str((std::istreambuf_iterator<char>(t)),
      std::istreambuf_iterator<char>());
    str = Haas::ScriptEngine::cleanComments(str);

    script.executeString(str);
    nlohmann::json version = script.getVar("version");
    nlohmann::json info    = script.getVar("ScenarioInfo");

    if (info.find("description") != info.end())
      _description = info["description"];
    else
      _description = "";

    if (info.find("name") != info.end())
      _name = info["name"];
    else
      _name = "unkown";

    if (info.find("type") != info.end()) {
      auto t = info["type"];
      if (t == "campaign")
        _type = ScenarioType::Campaign;
      else
        _type = ScenarioType::Skirmish;
    }
    else
      _type = ScenarioType::Skirmish;

    if (info.find("size") != info.end()) {
      _width  = info["size"][0];
      _height = info["size"][1];
    }
    else {
      _width  = 0;
      _height = 0;
    }


    if (info.find("map") != info.end())
      _map = info["map"];
    else
      _map = "";


    if (info.find("script") != info.end())
      _script = info["script"];
    else
      _script = "";


    if (info.find("save") != info.end())
      _save = info["save"];
    else
      _save = "";


    if (info.find("preview") != info.end())
      _preview = info["preview"];
    else
      _preview = "";
  }

  const std::string& Scenario::name() {
    return _name;
  }
  
  int Scenario::width() {
    return _width;
  }

  int Scenario::height() {
    return _height;
  }

  std::string Scenario::description() {
    return _description;
  }

  ScenarioType Scenario::type() {
    return _type;
  }

  const std::string& Scenario::map() {
    return _map;
  }

  const std::string& Scenario::save() {
    return _save;
  }

  const std::string& Scenario::script() {
    return _script;
  }

  const std::string& Scenario::preview() {
    return _preview;
  }
}