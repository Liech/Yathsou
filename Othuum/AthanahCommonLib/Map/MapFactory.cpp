#include "MapFactory.h"

#include "Map.h"
#include <filesystem>

namespace Athanah {
  MapFactory::MapFactory(const std::string& mapsFolder) {
    _mapFolder = mapsFolder + "\\";

    for (const auto& entry : std::filesystem::directory_iterator(_mapFolder)) {
      std::string path = entry.path().string();
      path = path.substr(_mapFolder.size());
      if (std::filesystem::exists(entry.path().string() + "/" + path + ".scmap"))
        _availableMaps.push_back(path);
    }
  }  

  std::shared_ptr<Map> MapFactory::loadMap(const std::string& name) {
    if (_loadedMaps.count(name))
      return _loadedMaps[name];
    _loadedMaps[name] = std::make_shared<Map>(_mapFolder, name);
    return _loadedMaps[name];
  }

  const std::vector<std::string>& MapFactory::getAvailableMaps() {
    return _availableMaps;
  }

}