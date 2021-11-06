#pragma once

#include <string>
#include <memory>
#include <vector>
#include <map>
#include <functional>
#include "AezeselFileIOLib/lib/json.hpp"

namespace Athanah {
  class Blueprint;

  class BlueprintFactory {
  public:
    BlueprintFactory(const std::string& unitsFolder);
    ~BlueprintFactory() = default;

    std::shared_ptr<const Blueprint> loadModel(const std::string&);
    const std::vector<std::string>& getAvailableModels();

  private:
    std::string                                            _unitsPath;
    std::vector<std::string>                               _availableUnits;
    std::map<std::string, std::shared_ptr<const Blueprint>> _loadedUnits;

    std::shared_ptr<std::function<nlohmann::json(const nlohmann::json&)>> soundCall;
  };
}