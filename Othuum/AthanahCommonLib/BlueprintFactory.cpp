#include "BlueprintFactory.h"
#include "Blueprint.h"

#include <iostream>
#include <filesystem>

#include "HaasScriptingLib/ScriptEngine.h"
#include "AezeselFileIOLib/lib/json.hpp"

namespace Athanah {
  BlueprintFactory::BlueprintFactory(const std::string& unitsFolder) {
    _unitsPath = unitsFolder;

    for (const auto& entry : std::filesystem::directory_iterator(_unitsPath)) {
      std::string path = entry.path().string();
      path = path.substr(_unitsPath.size());
      if (std::filesystem::exists(entry.path().string() + "/" + path + "_unit.bp"))
        _availableUnits.push_back(path);
    }

    soundCall = std::make_shared< std::function<nlohmann::json(const nlohmann::json&)>>(
      [](const nlohmann::json& input) -> nlohmann::json
    {
      return 1;
    }
    );
  }

  std::shared_ptr<const Blueprint> BlueprintFactory::loadModel(const std::string& name) {
    if (_loadedUnits.count(name))
      return _loadedUnits[name];

    std::shared_ptr<std::function<nlohmann::json(const nlohmann::json&)>> UnitBlueprint = std::make_shared< std::function<nlohmann::json(const nlohmann::json&)>>(
      [&](const nlohmann::json& input) -> nlohmann::json
    {
      _loadedUnits[name] = std::make_shared<const Blueprint>(input);
      return 1;
    }
    );
    Haas::ScriptEngine script;
    script.registerFunction("UnitBlueprint", UnitBlueprint);
    script.registerFunction("Sound", soundCall);
    
    std::string path = _unitsPath + name + "\\" + name + "_unit.bp";
    try {
      script.executeFile(path);
    }
    catch(...) {
      std::cout << "ERROR in executing file. Maybe it does not exist or the # comments are not yet preprocessed" << std::endl;
      nlohmann::json input;
      input["Description"] = "<>" + name;
      _loadedUnits[name] = std::make_shared<const Blueprint>(input);
    }
    return _loadedUnits[name];
  }

  const std::vector<std::string>& BlueprintFactory::getAvailableModels() {
    return _availableUnits;
  }
}