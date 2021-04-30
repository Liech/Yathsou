#include "MapSelection.h"

#include <IyathuumCoreLib/lib/glm/gtc/matrix_transform.hpp>
#include <filesystem>

#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Widgets/Button.h"
#include "ListSelection.h"
#include "Graphic.h"

MapSelection::MapSelection(std::string mapPath, Iyathuum::glmAABB<2> area, Graphic& graphic) : _graphic(graphic) {
  _area = area;

  std::vector<std::string> maps;
  for (const auto& entry : std::filesystem::directory_iterator(mapPath)) {
    std::string path = entry.path().string();
    path = path.substr(mapPath.size() + 1);
    if (std::filesystem::exists(entry.path().string() + "/" + path + ".scmap"))
      maps.push_back(path);
  }

  _list = std::make_unique<ListSelection>(maps, maps, area, _graphic.getWindow(), [this](std::string newTexture) {
    
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
