#include "BlueprintFactory.h"
#include "AthanahCommonLib/SupCom/Blueprint/Blueprint.h"

#include <iostream>
#include <fstream>
#include <filesystem>

#include "HaasScriptingLib/ScriptEngine.h"
#include "AezeselFileIOLib/lib/json.hpp"

namespace Athanah {
  BlueprintFactory::BlueprintFactory(const std::string& unitsFolder) {
    _unitsPath = unitsFolder;

    for (const auto& entry : std::filesystem::directory_iterator(_unitsPath)) {
      std::string path = entry.path().string();
      path = path.substr(_unitsPath.size()+1);
      if (std::filesystem::exists(entry.path().string() + "\\" + path + "_unit.bp"))
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

    bool called = false;
    std::shared_ptr<std::function<nlohmann::json(const nlohmann::json&)>> UnitBlueprint = std::make_shared< std::function<nlohmann::json(const nlohmann::json&)>>(
      [&](const nlohmann::json& input) -> nlohmann::json
    {
      called = true;
      _loadedUnits[name] = std::make_shared<const Blueprint>(name,input);
      return 1;
    }
    );
    Haas::ScriptEngine script;
    script.registerFunction("UnitBlueprint", UnitBlueprint);
    script.registerFunction("Sound", soundCall);
    
    std::string path = _unitsPath + "\\" + name + "\\" + name + "_unit.bp";
    std::ifstream t(path);
    std::string str((std::istreambuf_iterator<char>(t)),
      std::istreambuf_iterator<char>());
    str = Haas::ScriptEngine::cleanComments(str);
    script.executeString(str);
    if (!called) {
      _loadedUnits[name] = std::make_shared<const Blueprint>(name);
    }
    return _loadedUnits[name];
  }

  const std::vector<std::string>& BlueprintFactory::getAvailableModels() {
    return _availableUnits;
  }
}