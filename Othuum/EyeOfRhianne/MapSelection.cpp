#include "MapSelection.h"

#include <IyathuumCoreLib/lib/glm/gtc/matrix_transform.hpp>
#include <filesystem>

#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Widgets/Button.h"
#include "AhwassaGraphicsLib/Core/Renderer.h"
#include "AhwassaGraphicsLib/BasicRenderer/BasicRectangleRenderer.h"
#include "AhwassaGraphicsLib/BasicRenderer/BasicTexture2DRenderer.h"
#include "AhwassaGraphicsLib/BasicRenderer/BasicTextRenderer.h"
#include "AhwassaGraphicsLib/Uniforms/Texture.h"

#include "ListSelection.h"
#include "Graphic.h"
#include "AthanahCommonLib/Scenario.h"
#include "AezeselFileIOLib/ImageIO.h"
#include "AezeselFileIOLib/SupremeCommander/SCMAP.h"

MapSelection::MapSelection(std::string mapPath, Iyathuum::glmAABB<2> area, Graphic& graphic) : _graphic(graphic) {
  _area = area;

  std::vector<std::string> maps;
  std::vector<std::string> niceNamesMaps;
  for (const auto& entry : std::filesystem::directory_iterator(mapPath)) {
    std::string path = entry.path().string();
    path = path.substr(mapPath.size() + 1);
    if (std::filesystem::exists(entry.path().string() + "/" + path + ".scmap")) {
      _scenarios[path] = map();        
      _scenarios[path].scenario = std::make_shared<Athanah::Scenario>(mapPath + "/" + path + "/" + path + "_scenario.lua");
      _scenarios[path].preview = std::make_shared<Ahwassa::Texture>("Preview", 0);
      if (_scenarios[path].scenario->preview() != "") {
        std::string previewPath = _scenarios[path].scenario->preview();
        std::string p = mapPath + "/.." +previewPath;
        //if (std::filesystem::exists(p))
        //  _scenarios[path].preview = std::make_shared<Ahwassa::Texture>("Preview", Aezesel::ImageIO::readImage(p).get());
      }
      _scenarios[path].name = _scenarios[path].scenario->name();
      //_scenarios[path].map = std::make_shared<Aezesel::SCMAP>(mapPath + "/" + path + "/" + path + ".scmap");
      maps.push_back(path);
      niceNamesMaps.push_back(_scenarios[path].scenario->name());
    }
  }

  _list = std::make_unique<ListSelection>(maps, niceNamesMaps, area, _graphic.getWindow(), [mapPath,this](std::string newMap) {
    Athanah::Scenario s(mapPath + "/" + newMap + "/" + newMap + "_scenario.lua");
    std::string scmapPath = mapPath + "/" + newMap + "/" + newMap + ".scmap";
    Aezesel::SCMAP reader;
    auto map = reader.load(scmapPath);
    _previewImage = std::make_shared<Ahwassa::Texture>("Preview", map->previewImage.get());
  }, [this](Iyathuum::glmAABB<2> loc, std::string name, bool hovered) {
    _graphic.getWindow()->renderer().rectangle().start();
    _graphic.getWindow()->renderer().rectangle().drawRectangle(loc, hovered ? Iyathuum::Color(0.8f * 255, 0.8f * 255, 0.8f * 255) : Iyathuum::Color(0.4f * 255, 0.4f * 255, 0.4f * 255));
    _graphic.getWindow()->renderer().rectangle().end();
    _graphic.getWindow()->renderer().texture().start();
    Iyathuum::glmAABB<2> textureLoc = loc;
    textureLoc.setSize(glm::vec2(textureLoc.getSize()[1], textureLoc.getSize()[1]));
    _graphic.getWindow()->renderer().texture().draw(*_scenarios[name].preview, textureLoc);
    _graphic.getWindow()->renderer().texture().end();
    _graphic.getWindow()->renderer().text().start();
    _graphic.getWindow()->renderer().text().drawText(_scenarios[name].name, loc.getPosition() + glm::vec2(textureLoc.getSize()[0], 0),0.6f);
    _graphic.getWindow()->renderer().text().end();
  });
  _list->setVisible(false);
}

void MapSelection::setVisible(bool value) {
  _list->setVisible(value);
}

bool MapSelection::isVisible() {
  return _list->isVisible();
}

void MapSelection::update() {

}

void MapSelection::draw() {
  _list->draw();
  if (_previewImage) {
    Iyathuum::glmAABB<2> textureLoc(glm::vec2(_graphic.getWindow()->getWidth()-400, 0), glm::vec2(400, 400));
    _graphic.getWindow()->renderer().texture().start();
    _graphic.getWindow()->renderer().texture().draw(*_previewImage, textureLoc);
    _graphic.getWindow()->renderer().texture().end();
  }
}
