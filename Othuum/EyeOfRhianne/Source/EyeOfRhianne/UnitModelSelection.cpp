#include "UnitModelSelection.h"

#include "ListSelection.h"
#include "Graphic.h"

#include <glm/gtc/matrix_transform.hpp>
#include "HaasScriptingLib/ScriptEngine.h"

#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Core/Renderer.h"
#include "AhwassaGraphicsLib/Widgets/Button.h"
#include "AhwassaGraphicsLib/Renderer/BasicTextRenderer.h"
#include "AhwassaGraphicsLib/Renderer/BasicRectangleRenderer.h"
#include "AhwassaGraphicsLib/Renderer/BasicTexture2DRenderer.h"

#include "AthanahCommonLib/SupCom/Gamedata/Gamedata.h"
#include "AthanahCommonLib/SupCom/Gamedata/SupComModelFactory.h"
#include "AthanahCommonLib/SupCom/Gamedata/UiTextureFactory.h"
#include "AthanahCommonLib/SupCom/Gamedata/BlueprintFactory.h"
#include "AthanahCommonLib/SupCom/SupComModel.h"
#include "AthanahCommonLib/SupCom/Blueprint/Blueprint.h"
#include "AthanahCommonLib/SupCom/Blueprint/BlueprintGeneral.h"
#include "AthanahCommonLib/SupCom/Blueprint/BlueprintDisplay.h"

UnitModelSelection::UnitModelSelection(Athanah::Gamedata& gamedata, Iyathuum::glmAABB<2> area, std::function<void()> disableAllCall, Graphic& graphic) : 
  _graphic(graphic),
  _gamedata(gamedata)
{
  _disableAllCall = disableAllCall;

  Iyathuum::glmAABB<2> categoriesArea(area.getPosition()                  , glm::vec2(50                  , area.getSize()[1]));
  Iyathuum::glmAABB<2> modelArea     (area.getPosition() + glm::vec2(50,0), glm::vec2(area.getSize()[0]-50, area.getSize()[1]));


  std::vector<std::string> categories = {"UEF","Cybran","Aeon","Seraphim","Other","NonUnit"};

  for (int i = 0; i < categories.size(); i++) {
    auto names = getNames(categories[i]);
    std::unique_ptr<ListSelection> x = std::make_unique<ListSelection>(names.first, names.second, modelArea, _graphic.getWindow(), [this](std::string newModel) {
      setModel(newModel);
    }, [this](Iyathuum::glmAABB<2> loc, std::string name, bool hovered) {
      drawIcons(loc, name, hovered);
    });
    x->setVisible(false);
    _lists.push_back(std::move(x));
  }

  _categories = std::make_unique<ListSelection>(categories, categories, categoriesArea, _graphic.getWindow(), [this](std::string newModel) {
    for (int i = 0; i < _lists.size(); i++)
      _lists[i]->setVisible(false);
    int nr = getNumber(newModel);
    _lists[nr]->setVisible(true);
    _currentList = nr;

  }, [this](Iyathuum::glmAABB<2> loc, std::string name, bool hovered) {
    _graphic.getWindow()->renderer().rectangle().start();
    _graphic.getWindow()->renderer().rectangle().drawRectangle(loc, hovered ? Iyathuum::Color(0.8f * 255, 0.8f * 255, 0.8f * 255) : Iyathuum::Color(0.4f * 255, 0.4f * 255, 0.4f * 255));
    _graphic.getWindow()->renderer().rectangle().end();
    _graphic.getWindow()->renderer().texture().start();
    _graphic.getWindow()->renderer().texture().draw(*getFaction(name),loc);
    _graphic.getWindow()->renderer().texture().end();
  });

  initScript();
}

void UnitModelSelection::setModel(std::string newModel) {
  _currentID = newModel;
  _graphic.setModel(getCurrentModel());
  float scale = _gamedata.blueprint().loadModel(_currentID)->display().scale() * 30;
  _graphic._mesh->transformation = glm::scale(glm::mat4(1), glm::vec3(scale, scale, scale));
}


int UnitModelSelection::getNumber(std::string s) {
  if (s == "UEF")
    return 0;
  else if (s == "Cybran")
    return 1;
  else if (s == "Aeon")
    return 2;
  else if (s == "Seraphim")
    return 3;
  else if (s == "Other")
    return 4;
  return 5;
}
std::shared_ptr<Ahwassa::Texture> UnitModelSelection::getFaction(std::string s) {
  if (s == "UEF")
    return _gamedata.icon().getFactionIcon(Athanah::Faction::Uef, Athanah::FactionIconType::Normal);
  else if (s == "Cybran")
    return _gamedata.icon().getFactionIcon(Athanah::Faction::Cybran, Athanah::FactionIconType::Normal);
  else if (s == "Aeon")
    return _gamedata.icon().getFactionIcon(Athanah::Faction::Aeon, Athanah::FactionIconType::Normal);
  else if (s == "Seraphim")
    return _gamedata.icon().getFactionIcon(Athanah::Faction::Seraphim, Athanah::FactionIconType::Normal);
  else if (s == "Other")
    return _gamedata.icon().getFactionIcon(Athanah::Faction::Undefined, Athanah::FactionIconType::Normal);
  return _gamedata.icon().getTierIcons(Athanah::Faction::Uef,Athanah::TechLevel::T4);
}

void UnitModelSelection::drawIcons(Iyathuum::glmAABB<2> location, std::string name, bool hovered) {
  auto bp = _gamedata.blueprint().loadModel(name);

  _graphic.getWindow()->renderer().rectangle().start();
  _graphic.getWindow()->renderer().rectangle().drawRectangle(location, hovered ? Iyathuum::Color(0.8f * 255, 0.8f * 255, 0.8f * 255) : Iyathuum::Color(0.4f * 255, 0.4f * 255, 0.4f * 255));
  _graphic.getWindow()->renderer().rectangle().end();

  _graphic.getWindow()->renderer().texture().start();

  auto icon = _gamedata.icon().getIcon(name);
  location.setSize(glm::vec2(location.getSize()[1], location.getSize()[1]));
  _graphic.getWindow()->renderer().texture().draw(*_gamedata.icon().getBackgroundIcon(bp->general().icon(),hovered? Athanah::ButtonStatus::Hover:Athanah::ButtonStatus::Normal), location);
  _graphic.getWindow()->renderer().texture().draw(*icon, location);
  Iyathuum::glmAABB<2> factionIconLoc(location.getPosition() + glm::vec2(location.getSize()[0],0), glm::vec2(20, 20));
  _graphic.getWindow()->renderer().texture().draw(*_gamedata.icon().getFactionIcon(bp->general().faction(), Athanah::FactionIconType::Normal), factionIconLoc);
  Iyathuum::glmAABB<2> stratIconLoc(location.getPosition() + glm::vec2(location.getSize()[0],location.getSize()[1]-20), glm::vec2(20, 20));
  _graphic.getWindow()->renderer().texture().draw(*_gamedata.icon().getStrategicIcon(bp->strategicIcon(), Athanah::SelectableButtonStatus::Normal), stratIconLoc);

  _graphic.getWindow()->renderer().texture().end();
  _graphic.getWindow()->renderer().text().start();

  std::string text = bp->description() + "\n" + bp->general().unitName();

  _graphic.getWindow()->renderer().text().drawText(text,location.getPosition() + glm::vec2(location.getSize()[0] + 20,0),0.3f);
  _graphic.getWindow()->renderer().text().end();
}

std::shared_ptr<Athanah::SupComModel> UnitModelSelection::getCurrentModel() {
  return _gamedata.model().loadModel(_currentID);
}

void UnitModelSelection::setVisible(bool value) {
  _categories->setVisible(value);
  _lists[_currentList]->setVisible(value);
}

bool UnitModelSelection::isVisible() {
  return _categories->isVisible();
}

void UnitModelSelection::update() {
}

void UnitModelSelection::draw() {
  _lists[_currentList]->draw();
  _categories->draw();
}

std::pair<std::vector<std::string>, std::vector<std::string>> UnitModelSelection::getNames(std::string category) {
  std::vector<std::string> names    ;
  std::vector<std::string> niceNames;

  for (auto x : _gamedata.model().getAvailableModels()) {
    if (!_gamedata.blueprint().hasBlueprint(x))
      continue;
    auto bp = _gamedata.blueprint().loadModel(x);
    auto faction = bp->general().faction();
    bool ok = 
      (category == "UEF"     && faction == Athanah::Faction::Uef      ) ||
      (category == "Cybran"  && faction == Athanah::Faction::Cybran   ) ||
      (category == "Aeon"    && faction == Athanah::Faction::Aeon     ) ||
      (category == "Seraphim"&& faction == Athanah::Faction::Seraphim ) ||
      (category == "Other"   && faction == Athanah::Faction::Undefined)
      ;
    if (ok) {
      names    .push_back(x);
      niceNames.push_back(bp->description() + "\n" + bp->general().unitName());
    }
  }
  return std::make_pair(names,niceNames);
}

void UnitModelSelection::initScript() {
  _setUnit = std::make_shared< std::function<nlohmann::json(const nlohmann::json&)>>(
    [&](const nlohmann::json& input) -> nlohmann::json
  {
    std::string name = input;
    setModel(name);
    return 1;
  }
  );
  _getUnit = std::make_shared< std::function<nlohmann::json(const nlohmann::json&)>>(
    [&](const nlohmann::json& input) -> nlohmann::json
  {
    return _currentID;
  }
  );
  _getAllUnits = std::make_shared< std::function<nlohmann::json(const nlohmann::json&)>>(
    [&](const nlohmann::json& input) -> nlohmann::json
  {
    return _gamedata.model().getAvailableModels();
  }
  );
  _getBlueprint = std::make_shared< std::function<nlohmann::json(const nlohmann::json&)>>(
    [&](const nlohmann::json& input) -> nlohmann::json
  {
    return _gamedata.blueprint().loadModel(input)->getRaw();
  }
  );
  _setUnitColor = std::make_shared< std::function<nlohmann::json(const nlohmann::json&)>>(
    [&](const nlohmann::json& input) -> nlohmann::json
  {
    Iyathuum::Color clr(input[0], input[1], input[2],input[3]);
    _graphic._mesh->teamColor = clr;
    return 1;
  }
  );
  _graphic._scripts->registerFunction("eyeSetUnit"     , _setUnit     );
  _graphic._scripts->registerFunction("eyeGetAllUnits" , _getAllUnits );
  _graphic._scripts->registerFunction("eyeGetUnit"     , _getUnit     );
  _graphic._scripts->registerFunction("eyeGetBlueprint", _getBlueprint);
  _graphic._scripts->registerFunction("eyeSetUnitColor", _setUnitColor);

}