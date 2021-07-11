#pragma once

#include <string>
#include <memory>
#include "AezeselFileIOLib/SupremeCommander/SCMAP.h"

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
    Aezesel::SCMAP::Map&              scmap();
    void                              loadFull();
  private:
    std::string                           _directory;
    std::string                           _name     ;
    std::shared_ptr<Scenario>             _scenario ;
    std::shared_ptr<Ahwassa::Texture>     _preview  = nullptr;
    std::unique_ptr< Aezesel::SCMAP::Map> _scmap    = nullptr;
  };
}