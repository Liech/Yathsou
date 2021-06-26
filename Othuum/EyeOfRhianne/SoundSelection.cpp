#include "SoundSelection.h"

#include <IyathuumCoreLib/lib/glm/gtc/matrix_transform.hpp>
#include <filesystem>

#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Widgets/Button.h"
#include "AhwassaGraphicsLib/Core/Renderer.h"
#include "AhwassaGraphicsLib/BasicRenderer/BasicRectangleRenderer.h"
#include "AhwassaGraphicsLib/BasicRenderer/BasicTexture2DRenderer.h"
#include "AhwassaGraphicsLib/BasicRenderer/BasicTextRenderer.h"
#include "AhwassaGraphicsLib/Uniforms/Texture.h"
#include "AhwassaGraphicsLib/Geometry/HeightFieldMeshGenerator.h"
#include "AhwassaGraphicsLib/Vertex/PositionColorNormalVertex.h"

#include "ListSelection.h"
#include "Graphic.h"

SoundSelection::SoundSelection(std::string soundPath, Iyathuum::glmAABB<2> area, Graphic& graphic) : _graphic(graphic) {
  _area = area;

  std::vector<std::string> availableBanks;
  for (const auto& p : std::filesystem::recursive_directory_iterator(soundPath)) {
    if (p.path().extension() == ".xsb") {
      std::string name = p.path().string().substr(soundPath.size() + 1);
      name = name.substr(0, name.size() - 4);
      availableBanks.push_back(name);
    }
  }

  _list = std::make_unique<ListSelection>(availableBanks, availableBanks, area, _graphic.getWindow(), [this](std::string newMap) {

  });
  _list->setVisible(false);
}

void SoundSelection::setVisible(bool value) {
  _list->setVisible(value);
}

bool SoundSelection::isVisible() {
  return _list->isVisible();
}

void SoundSelection::update() {

}

void SoundSelection::draw() {
  _list->draw();

}
