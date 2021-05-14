#pragma once

#include <string>
#include <memory>
#include <vector>
#include <map>

namespace Aezesel {
  class ZIP;
}

namespace Athanah {
  class SupComModel;

  class SupComModelFactory {
  public:
    SupComModelFactory(const std::string& unitsFolder);

    std::shared_ptr<SupComModel> loadModel(const std::string&);
    const std::vector<std::string>&     getAvailableModels();

  private:
    std::string              _unitsPath;
    std::vector<std::string> _availableUnits;
    std::map<std::string, std::shared_ptr<SupComModel>> _loadedUnits;
  };
}