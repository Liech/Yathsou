#include "AssetSelection.h"

#include "UnitModelSelection.h"
#include "AnimationSelection.h"
#include "SkyBoxSelection.h"
#include "RendererSelection.h"
#include "ListSelection.h"
#include "MapSelection.h"
#include "SoundSelection.h"
#include "ScriptSelection.h"
#include "Graphic.h"

#include <glm/gtc/matrix_transform.hpp>
#include "IyathuumCoreLib/BaseTypes/glmAABB.h"
#include "AthanahCommonLib/SupCom/Gamedata/Gamedata.h"

#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Widgets/ListLayout.h"

AssetSelection::AssetSelection(EyeOfRhianneConfiguration& config, Iyathuum::glmAABB<2> area, Graphic& graphic) : _graphic(graphic), _config(config){
  _area = area;

  _gamedata = std::make_unique<Athanah::Gamedata>(config.SupComPath,true);

  std::vector<std::string> options;
  options.push_back("Units");
  options.push_back("Animation");
  options.push_back("SkyBox");
  options.push_back("Renderer");
  options.push_back("Map");
  options.push_back("Scripts");
  options.push_back("Sound");

  _list = std::make_unique<ListSelection>(options, options, area, _graphic.getWindow(), [this](std::string newSelection) {    
    unitVisibility(newSelection);
  });

  addSelections();
}  

void AssetSelection::addSelections() {
  Iyathuum::glmAABB<2> area(_area.getPosition() +glm::vec2(300,0),_area.getSize());

  _units = std::make_shared<UnitModelSelection>(*_gamedata,area,[this]() {unitVisibility(false); }, _graphic);

  _animation  = std::make_shared<AnimationSelection> (area, _graphic);
  _skyBox     = std::make_shared<SkyBoxSelection>    (_gamedata->skybox(),area, _graphic);
  _renderer   = std::make_shared<RendererSelection>  (area,_graphic);
  _maps       = std::make_shared<MapSelection>       (_config.SupComPath+ "\\maps",area,_graphic, *_gamedata);
  _scripts    = std::make_shared<ScriptSelection>    (area,_graphic);
  _sounds     = std::make_shared<SoundSelection >    (_config.SupComPath + "\\sounds",area,_graphic);
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
  if (_current == "Map")
    _maps->setVisible(!_maps->isVisible());
  if (_current == "Scripts")
    _scripts->setVisible(!_scripts->isVisible());
  if (_current == "Sound")
    _sounds->setVisible(!_sounds->isVisible());
}

void AssetSelection::hideAll() {
  _units     ->setVisible(false);
  _animation ->setVisible(false);
  _skyBox    ->setVisible(false);
  _renderer  ->setVisible(false);
  _maps      ->setVisible(false);
  _scripts   ->setVisible(false);
  _sounds    ->setVisible(false);
}

void AssetSelection::draw() {
  _units     ->draw();
  _animation ->draw();
  _skyBox    ->draw();
  _renderer  ->draw();
  _maps      ->draw();
  _scripts   ->draw();
  _sounds    ->draw();
  _list      ->draw();
}

void AssetSelection::update() {
  _units     ->update();
  _animation ->update();
  _skyBox    ->update();
  _renderer  ->update();
  _maps      ->update();
  _scripts   ->update();
  _sounds    ->update();
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
