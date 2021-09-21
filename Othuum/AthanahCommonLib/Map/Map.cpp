#include "Map.h"

#include "AezeselFileIOLib/SupremeCommander/SCMAP.h"
#include "Scenario.h"
#include "AhwassaGraphicsLib/Uniforms/Texture.h"

namespace Athanah {
  Map::Map(const std::string& unitDir, const std::string& mapName) {
    _directory = unitDir;
    _name      = mapName;
    _scenario = std::make_shared<Scenario>(_directory + "\\" + _name + "\\" + _name + "_scenario.lua");
  }

  Scenario& Map::getScenario() {
    return *_scenario;
  }

  std::shared_ptr<Ahwassa::Texture> Map::getPreview() {
    if (_preview == nullptr) {
      Aezesel::SCMAP loader;
      auto img = loader.loadPreview(_directory + "\\" + _name + "\\" + _name + ".scmap");
      _preview = std::make_shared<Ahwassa::Texture>("Preview", img.get());
    }
    return _preview;
  }

  void Map::loadFull() {
    if (_scmap)
      return;
    Aezesel::SCMAP loader;
    _scmap = std::move(loader.load(_directory + "\\" + _name + "\\" + _name + ".scmap"));
  }

  Aezesel::SCMAP::Map& Map::scmap() {
    return *_scmap;
  }

  Iyathuum::glmAABB<3> Map::aabb() {
    return Iyathuum::glmAABB<3>(glm::vec3(-50, -50, -50), glm::vec3(200, 200, 200));
  }
}