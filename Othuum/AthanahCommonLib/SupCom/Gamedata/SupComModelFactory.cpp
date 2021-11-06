#include "SupComModelFactory.h"

#include "AezeselFileIOLib/SupremeCommander/SCD.h"
#include "SupCom/SupComModel.h"
#include <filesystem>

namespace Athanah {
  SupComModelFactory::SupComModelFactory(const std::string& unitsFolder) {
    _archive = std::make_unique<Aezesel::SCD>(unitsFolder);

    for (const auto& entry : _archive->getDirectories()) {
      if (_archive->fileExists(entry + "/" + entry + "_lod0.scm"))
        _availableUnits.push_back(entry);
    }
  }

  std::shared_ptr<SupComModel> SupComModelFactory::loadModel(const std::string& name) {
    if (_loadedUnits.count(name))
      return _loadedUnits[name];
    _loadedUnits[name] = std::make_shared<SupComModel>(*_archive, name);
    return _loadedUnits[name];    
  }

  const std::vector<std::string>& SupComModelFactory::getAvailableModels() {
    return _availableUnits;
  }

}