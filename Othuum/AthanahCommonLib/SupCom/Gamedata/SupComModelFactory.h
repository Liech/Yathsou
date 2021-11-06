#pragma once

#include <string>
#include <memory>
#include <vector>
#include <map>

namespace Aezesel {
  class SCD;
}

namespace Athanah {
  class SupComModel;

  class SupComModelFactory {
  public:
    //unit Folder can also be a zip file ending with .scd
    SupComModelFactory(const std::string& unitsFolder);
    virtual ~SupComModelFactory() = default;
    
    std::shared_ptr<SupComModel> loadModel(const std::string&);
    const std::vector<std::string>&     getAvailableModels();

  private:
    std::unique_ptr<Aezesel::SCD>                       _archive;
    std::vector<std::string>                            _availableUnits;
    std::map<std::string, std::shared_ptr<SupComModel>> _loadedUnits;
  };
}