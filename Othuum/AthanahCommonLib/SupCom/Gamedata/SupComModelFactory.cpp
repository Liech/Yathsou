#include "SupComModelFactory.h"

#include "SupCom/SupComModel.h"
#include <filesystem>

namespace Athanah {
  SupComModelFactory::SupComModelFactory(const std::string& unitsFolder) {
    if (unitsFolder.ends_with(".scd"))
      throw std::runtime_error("Not yet implemented!");
    _unitsPath = unitsFolder + "\\";

    for (const auto& entry : std::filesystem::directory_iterator(_unitsPath)) {
      std::string path = entry.path().string();
      path = path.substr(_unitsPath.size());
      if (std::filesystem::exists(entry.path().string() + "/" + path + "_lod0.scm"))
        _availableUnits.push_back(path);
    }
  }

  std::shared_ptr<SupComModel> SupComModelFactory::loadModel(const std::string& name) {
    if (_loadedUnits.count(name))
      return _loadedUnits[name];
    _loadedUnits[name] = std::make_shared<SupComModel>(_unitsPath, name);
    return _loadedUnits[name];    
  }

  const std::vector<std::string>& SupComModelFactory::getAvailableModels() {
    return _availableUnits;
  }

}