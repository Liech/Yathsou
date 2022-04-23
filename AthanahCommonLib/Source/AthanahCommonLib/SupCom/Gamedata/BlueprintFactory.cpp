#include "BlueprintFactory.h"
#include "AthanahCommonLib/SupCom/Blueprint/Blueprint.h"

#include <iostream>
#include <fstream>
#include <filesystem>

#include "HaasScriptingLib/ScriptEngine.h"
#include <nlohmann/json.hpp>
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
    soundCall = std::make_shared< std::function<nlohmann::json(const nlohmann::json&)>>(
      [](const nlohmann::json& input) -> nlohmann::json {
        return 1;
      }
    );

    for (const auto& entry : _archive->getDirectories()) {
      if (_archive->fileExists(entry + "\\" + entry + "_unit.bp")) {
        auto modl = loadModel(entry);
        if (modl->invalid())
          continue;
        _availableUnits.push_back(entry);
      }
    }
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

  std::set<std::string> BlueprintFactory::getModelsByCategory(UnitCategory cat) {
    std::set<std::string> result;
    for (auto& x : _availableUnits) {
      if (loadModel(x)->hasCategory(cat))
        result.insert(x);
    }
    return result;
  }

  std::set<std::string> BlueprintFactory::getModelsByCategory(const std::set<UnitCategory>& filter) {
    std::set<std::string> units(getAvailableModels().begin(), getAvailableModels().end());
    for (auto& x : filter) {
      std::set<std::string> intersection;
      auto intersecter = getModelsByCategory(x);
      std::set_intersection(units.begin(), units.end(), intersecter.begin(), intersecter.end(), std::inserter(intersection, intersection.begin()));
      units = intersection;
    }
    return units;
  }
}