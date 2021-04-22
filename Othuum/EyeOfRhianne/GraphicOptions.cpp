#include "GraphicOptions.h"

#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Widgets/Button.h"
#include "AhwassaGraphicsLib/Uniforms/Texture.h"
#include "IyathuumCoreLib/BaseTypes/glmAABB.h"
#include "ListSelection.h"

GraphicOptions::GraphicOptions(std::vector<std::shared_ptr<Ahwassa::Texture>> textures,std::function<void()> disableAllCall, Ahwassa::Window* w) {
  _window = w;
  _disableAllCall = disableAllCall;

  _showHide = std::make_shared<Ahwassa::Button>("Graphic", Iyathuum::glmAABB<2>(glm::vec2(300, w->getHeight() - 50), glm::vec2(300, 50)), [this]() {
    _disableAllCall();
    setVisible(!isVisible());
  }, w);

  std::vector<std::string> textureNames;
  for (int i = 0; i < textures.size(); i++){
    _textures[textures[i]->getName()] = textures[i];
    textureNames.push_back(textures[i]->getName());
  }
  _currentTexture = textures[0];

  _list = std::make_unique<ListSelection>(textureNames,textureNames, Iyathuum::glmAABB<2>(glm::vec2(0,0),glm::vec2(300,w->getHeight() / 2)), w, [this](std::string newTexture) {
    _currentTexture = _textures[newTexture];
  });
  _list->setVisible(false);
}

void GraphicOptions::drawUI() {
  _showHide->draw();
  _list->draw();
}


void GraphicOptions::update() {

}

void GraphicOptions::setVisible(bool visible) {
  _visible = visible;
  _list->setVisible(visible);
}

bool GraphicOptions::isVisible() {
  return _visible;
}

std::shared_ptr<Ahwassa::Texture> GraphicOptions::getCurrentTexture() {
  return _currentTexture;
}