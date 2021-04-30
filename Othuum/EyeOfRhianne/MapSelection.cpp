#include "MapSelection.h"

#include <IyathuumCoreLib/lib/glm/gtc/matrix_transform.hpp>
#include <filesystem>

#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Widgets/Button.h"
#include "ListSelection.h"
#include "Graphic.h"
#include "AthanahCommonLib/Scenario.h"

MapSelection::MapSelection(std::string mapPath, Iyathuum::glmAABB<2> area, Graphic& graphic) : _graphic(graphic) {
  _area = area;

  std::vector<std::string> maps;
  std::vector<std::string> niceNamesMaps;
  for (const auto& entry : std::filesystem::directory_iterator(mapPath)) {
    std::string path = entry.path().string();
    path = path.substr(mapPath.size() + 1);
    if (std::filesystem::exists(entry.path().string() + "/" + path + ".scmap")) {
      _scenarios[path] = std::make_shared<Athanah::Scenario>(mapPath + "/" + path + "/" + path + "_scenario.lua");
      maps.push_back(path);
      niceNamesMaps.push_back(_scenarios[path]->name());
    }
  }

  _list = std::make_unique<ListSelection>(maps, niceNamesMaps, area, _graphic.getWindow(), [mapPath,this](std::string newMap) {
    Athanah::Scenario s(mapPath + "/" + newMap + "/" + newMap + "_scenario.lua");
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
