#pragma once

#include <string>
#include <memory>
#include <vector>
#include <map>

namespace Aezesel {
  class ZIP;
}

namespace Athanah {
  class Map;

  class MapFactory {
  public:
    MapFactory(const std::string& mapFolder);

    std::shared_ptr<Map>            loadMap(const std::string&);
    const std::vector<std::string>& getAvailableMaps();

  private:
    std::string                                 _mapFolder    ;
    std::vector<std::string>                    _availableMaps;
    std::map<std::string, std::shared_ptr<Map>> _loadedMaps   ;
  };
}