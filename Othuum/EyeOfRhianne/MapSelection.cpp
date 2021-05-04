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
#include "AthanahCommonLib/Map/Scenario.h"
#include "AthanahCommonLib/Map/Map.h"
#include "AthanahCommonLib/Map/MapFactory.h"
#include "AezeselFileIOLib/ImageIO.h"
#include "AezeselFileIOLib/SupremeCommander/SCMAP.h"

MapSelection::MapSelection(std::string mapPath, Iyathuum::glmAABB<2> area, Graphic& graphic) : _graphic(graphic) {
  _area = area;
  _factory = std::make_shared<Athanah::MapFactory>(mapPath);

  std::vector<std::string> maps;
  std::vector<std::string> niceNamesMaps;
  for (auto entry : _factory->getAvailableMaps()) {
    maps.push_back(entry);
    auto map = _factory->loadMap(entry);
    niceNamesMaps.push_back(map->getScenario().name());

  }

  _list = std::make_unique<ListSelection>(maps, niceNamesMaps, area, _graphic.getWindow(), [mapPath,this](std::string newMap) {


  }, [this](Iyathuum::glmAABB<2> loc, std::string name, bool hovered) {
    _graphic.getWindow()->renderer().rectangle().start();
    _graphic.getWindow()->renderer().rectangle().drawRectangle(loc, hovered ? Iyathuum::Color(0.8f * 255, 0.8f * 255, 0.8f * 255) : Iyathuum::Color(0.4f * 255, 0.4f * 255, 0.4f * 255));
    _graphic.getWindow()->renderer().rectangle().end();
    _graphic.getWindow()->renderer().texture().start();
    Iyathuum::glmAABB<2> textureLoc = loc;
    auto map = _factory->loadMap(name);
    textureLoc.setSize(glm::vec2(textureLoc.getSize()[1], textureLoc.getSize()[1]));
    _graphic.getWindow()->renderer().texture().draw(*map->getPreview(), textureLoc);
    _graphic.getWindow()->renderer().texture().end();
    _graphic.getWindow()->renderer().text().start();
    _graphic.getWindow()->renderer().text().drawText(map->getScenario().name(), loc.getPosition() + glm::vec2(textureLoc.getSize()[0], 0),0.6f);
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
}
