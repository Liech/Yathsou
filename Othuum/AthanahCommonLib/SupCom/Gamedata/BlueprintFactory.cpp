#include "BlueprintFactory.h"
#include "AthanahCommonLib/SupCom/Blueprint/Blueprint.h"

#include <iostream>
#include <fstream>
#include <filesystem>

#include "HaasScriptingLib/ScriptEngine.h"
#include "AezeselFileIOLib/lib/json.hpp"
#include "AezeselFileIOLib/SupremeCommander/SCD.h"

namespace Athanah {
  BlueprintFactory::BlueprintFactory(const std::string& unitsFolder) {
    _archive = std::make_shared<Aezesel::SCD>(unitsFolder);
    init();
  }

  BlueprintFactory::BlueprintFactory(std::shared_ptr<Aezesel::SCD> archive) {
    _archive = archive;
    init();
  }

  void BlueprintFactory::init() {
    for (const auto& entry : _archive->getDirectories()) {
      if (_archive->fileExists(entry + "\\" + entry + "_unit.bp"))
        _availableUnits.push_back(entry);
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
    
    std::string path = name + "\\" + name + "_unit.bp";
    std::string str = _archive->loadTextFile(path);
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

  bool BlueprintFactory::hasBlueprint(const std::string& name) const {
    std::string path = name + "\\" + name + "_unit.bp";
    return _archive->fileExists(path);
  }

}