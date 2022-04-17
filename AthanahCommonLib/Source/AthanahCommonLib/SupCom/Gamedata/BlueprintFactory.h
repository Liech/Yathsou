#pragma once

#include <string>
#include <memory>
#include <vector>
#include <map>
#include <functional>
#include <nlohmann/json.hpp>

namespace Aezesel {
  class SCD;
}

namespace Athanah {
  class Blueprint;

  class BlueprintFactory {
  public:
    BlueprintFactory(const std::string& unitsFolder);
    BlueprintFactory(std::shared_ptr<Aezesel::SCD>);
    virtual ~BlueprintFactory() = default;

    std::shared_ptr<const Blueprint> loadModel(const std::string&);
    const std::vector<std::string>&  getAvailableModels();
    bool                             hasBlueprint(const std::string&) const;
  private:
    void init();

    std::shared_ptr<Aezesel::SCD>                           _archive;
    std::vector<std::string>                                _availableUnits;
    std::map<std::string, std::shared_ptr<const Blueprint>> _loadedUnits;

    std::shared_ptr<std::function<nlohmann::json(const nlohmann::json&)>> soundCall;
  };
}