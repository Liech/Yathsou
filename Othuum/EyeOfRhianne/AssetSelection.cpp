#include "AssetSelection.h"

#include "UnitModelSelection.h"
#include "AnimationSelection.h"
#include "SkyBoxSelection.h"
#include "RendererSelection.h"
#include "ListSelection.h"
#include "Graphic.h"

#include <IyathuumCoreLib/lib/glm/gtc/matrix_transform.hpp>
#include "IyathuumCoreLib/BaseTypes/glmAABB.h"

#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Widgets/ListLayout.h"

AssetSelection::AssetSelection(const std::string& path, Iyathuum::glmAABB<2> area, Graphic& graphic) : _graphic(graphic){
  _path = path;
  _area = area;
  std::vector<std::string> options;
  options.push_back("Units");
  options.push_back("Animation");
  options.push_back("SkyBox");
  options.push_back("Renderer");

  _list = std::make_unique<ListSelection>(options, options, area, _graphic.getWindow(), [this](std::string newSelection) {    
    unitVisibility(newSelection);
  });

  addSelections();
}  

void AssetSelection::addSelections() {
  Iyathuum::glmAABB<2> area(_area.getPosition() +glm::vec2(300,0),_area.getSize());

  _units = std::make_shared<UnitModelSelection>(_path,area,[this]() {unitVisibility(false); }, _graphic);

  _animation = std::make_shared<AnimationSelection>(area, _graphic);
  _skyBox    = std::make_shared<SkyBoxSelection>(_path + "\\textures\\environment",area, _graphic);
  _renderer  = std::make_shared<RendererSelection>(area,_graphic);
}

void AssetSelection::unitVisibility(std::string newMenu) {
  if (newMenu != _current)
    hideAll();
  _current = newMenu;
  if (_current == "Units")
    _units->setVisible(!_units->isVisible());
  if (_current == "Animation")
    _animation->setVisible(!_animation->isVisible());
  if (_current == "SkyBox")
    _skyBox->setVisible(!_skyBox->isVisible());
  if (_current == "Renderer")
    _renderer->setVisible(!_renderer->isVisible());
}

void AssetSelection::hideAll() {
  _units->setVisible(false);
  _animation->setVisible(false);
  _skyBox->setVisible(false);
  _renderer->setVisible(false);
}

void AssetSelection::draw() {
  _units->draw();
  _animation->draw();
  _skyBox->draw();
  _renderer->draw();
  _list->draw();
}

void AssetSelection::update() {
  _units->update();
  _animation->update();
  _skyBox->update();
  _renderer->update();
}

void AssetSelection::setVisible(bool visible) {
  _list->setVisible(visible);
  if (!visible)
    hideAll();
  else
    unitVisibility(_current);
}

bool AssetSelection::isVisible() {
  return _list->isVisible();
}
