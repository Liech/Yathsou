#pragma once

#include <string>
#include <memory>

namespace Ahwassa {
  class Texture;
}

namespace Athanah {
  class Scenario;
 
  class Map {
  public:
    Map(const std::string& unitDir, const std::string& mapName);

    std::shared_ptr<Ahwassa::Texture> getPreview();
    Scenario&                         getScenario();
    void                              loadFull();
  private:
    std::string                       _directory;
    std::string                       _name     ;
    std::shared_ptr<Scenario>         _scenario ;
    std::shared_ptr<Ahwassa::Texture> _preview  = nullptr;
  };
}