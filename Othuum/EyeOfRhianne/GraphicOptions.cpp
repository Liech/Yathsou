#include "GraphicOptions.h"

#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Widgets/Button.h"
#include "AhwassaGraphicsLib/Uniforms/Texture.h"
#include "IyathuumCoreLib/BaseTypes/glmAABB.h"
#include "ListSelection.h"
#include "AhwassaGraphicsLib/Widgets/Slider.h"
#include "AhwassaGraphicsLib/Widgets/Label.h"
#include "AhwassaGraphicsLib/Widgets/ListLayout.h"
#include "AhwassaGraphicsLib/PostProcessing/Bloom.h"

GraphicOptions::GraphicOptions(std::vector<std::shared_ptr<Ahwassa::Texture>> textures, std::shared_ptr<Ahwassa::Bloom> bloom, std::function<void()> disableAllCall, Ahwassa::Window* w) {
  _window = w;
  _disableAllCall = disableAllCall;
  _bloom = bloom;

  _showHide = std::make_shared<Ahwassa::Button>("Graphic", Iyathuum::glmAABB<2>(glm::vec2(300, w->getHeight() - 50), glm::vec2(300, 50)), [this]() {
    _disableAllCall();
    setVisible(!isVisible());
    _bloomOptions->setVisible(isVisible() && _currentTexture->getName() == "Bloom");
  }, w);

  std::vector<std::string> textureNames;
  for (int i = 0; i < textures.size(); i++){
    _textures[textures[i]->getName()] = textures[i];
    textureNames.push_back(textures[i]->getName());
  }
  _currentTexture = textures[0];

  _list = std::make_unique<ListSelection>(textureNames,textureNames, Iyathuum::glmAABB<2>(glm::vec2(0,0),glm::vec2(300,w->getHeight() / 2)), w, [this](std::string newTexture) {
    _currentTexture = _textures[newTexture];
    _bloomOptions->setVisible(isVisible() && _currentTexture->getName() == "Bloom");
  });
  makeBloomOptions();
  setVisible(false);
}

void GraphicOptions::makeBloomOptions() {
  _bloomOptions = std::make_shared<Ahwassa::ListLayout>(Iyathuum::glmAABB<2>(glm::vec2(0, _window->getHeight() / 2), glm::vec2(300, _window->getHeight() / 2 - 50)), _window);
  _bloomOptions->addLabel("Intensity");
  _bloomOptions->addSlider(8, 0, 50, [this](float value) {_bloom->setIntensity(value); });
  _bloomOptions->addLabel("Size");
  _bloomOptions->addSlider(8, 0, 50, [this](float value) {_bloom->setSize(value); });
  _bloomOptions->addLabel("Quality");
  _bloomOptions->addSlider(3, 0, 20, [this](float value) {_bloom->setQuality(value); });
  _bloomOptions->addLabel("Directions");
  _bloomOptions->addSlider(16, 0, 100, [this](float value) {_bloom->setDirections(value); });
  _bloomOptions->setMaximumSize(_bloomOptions->getLocalPosition().getSize());
  _bloomOptions->adjustSize();
  _bloomOptions->setCurrentScroll(_bloomOptions->getMaximumScroll());
}

void GraphicOptions::drawUI() {
  _showHide->draw();
  _list->draw();
  _bloomOptions->adjustSize();
  _bloomOptions->draw();
}

void GraphicOptions::update() {

}

void GraphicOptions::setVisible(bool visible) {
  _visible = visible;
  _list->setVisible(visible);
  _bloomOptions->setVisible(isVisible() && _currentTexture->getName() == "Bloom");  
}

bool GraphicOptions::isVisible() {
  return _visible;
}

std::shared_ptr<Ahwassa::Texture> GraphicOptions::getCurrentTexture() {
  return _currentTexture;
}
