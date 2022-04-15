#include "SoundSelection.h"

#include <glm/gtc/matrix_transform.hpp>
#include <filesystem>

#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Widgets/Button.h"
#include "AhwassaGraphicsLib/Core/Renderer.h"
#include "AhwassaGraphicsLib/Renderer/BasicRectangleRenderer.h"
#include "AhwassaGraphicsLib/Renderer/BasicTexture2DRenderer.h"
#include "AhwassaGraphicsLib/Renderer/BasicTextRenderer.h"
#include "AhwassaGraphicsLib/Uniforms/Texture.h"
#include "AhwassaGraphicsLib/Geometry/HeightFieldMeshGenerator.h"
#include "AhwassaGraphicsLib/Vertex/PositionColorNormalVertex.h"
#include "AhwassaGraphicsLib/sound/SoundEngine.h"

#include "AezeselFileIOLib/Sound/SoundFactory.h"

#include "ListSelection.h"
#include "Graphic.h"

SoundSelection::SoundSelection(std::string soundPath, Iyathuum::glmAABB<2> area, Graphic& graphic) : _graphic(graphic) {
  _area = area;

  _factory = std::make_shared<Aezesel::SoundFactory>(soundPath);
  _soundEngine = std::make_shared<Ahwassa::SoundEngine>();

  Iyathuum::glmAABB<2> soundArea(area);
  soundArea.setPosition(area.getPosition() + glm::vec2(area.getSize()[0], 0));

  _bankList = std::make_unique<ListSelection>(_factory->getAllBanks(), _factory->getAllBanks(), area, _graphic.getWindow(), [this,soundArea, soundPath](std::string bank) {
    std::vector<std::string> names = _factory->getAllSoundsInBank(bank);
    _soundList = std::make_unique<ListSelection>(names, names, soundArea, _graphic.getWindow(), [this,bank](std::string soundName) {
      _currentHandler = _soundEngine->createHandler(*_factory->load(bank,soundName));
      _currentHandler->play();
    });

  });
  _bankList->setVisible(false);

}

void SoundSelection::setVisible(bool value) {
  _bankList->setVisible(value);
  if (_soundList)
    _soundList->setVisible(value);
}

bool SoundSelection::isVisible() {
  return _bankList->isVisible();
}

void SoundSelection::update() {

}

void SoundSelection::draw() {
  _bankList->draw();
  if (_soundList)
    _soundList->draw();
}
