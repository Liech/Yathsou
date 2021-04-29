#include "RendererSelection.h"

#include "ListSelection.h"
#include "Graphic.h"
#include "AhwassaGraphicsLib/Uniforms/Texture.h"
#include "AhwassaGraphicsLib/Core/Window.h"

RendererSelection::RendererSelection(Iyathuum::glmAABB<2> area,Graphic& graphic) : _graphic(graphic){
  std::vector<std::string> textureNames;
  for (int i = 0; i < _graphic._textures.size(); i++) {
    _textures[_graphic._textures[i]->getName()] = i;
    textureNames.push_back(_graphic._textures[i]->getName());
  }

  _list = std::make_unique<ListSelection>(textureNames, textureNames,area, _graphic.getWindow(), [this](std::string newTexture) {
    _graphic._renderedTexture = _textures[newTexture];
  });
  _list->setVisible(false);
}

void RendererSelection::setVisible(bool value) {
  _list->setVisible(value);
}

bool RendererSelection::isVisible() {
  return _list->isVisible();
}

void RendererSelection::update() {

}

void RendererSelection::draw() {
  _list->draw();
}