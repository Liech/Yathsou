#include "UnitModelSelection.h"

#include "ListSelection.h"
#include "Graphic.h"


#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Core/Renderer.h"
#include "AhwassaGraphicsLib/Widgets/Button.h"
#include "AhwassaGraphicsLib/BasicRenderer/BasicTextRenderer.h"
#include "AhwassaGraphicsLib/BasicRenderer/BasicRectangleRenderer.h"
#include "AhwassaGraphicsLib/BasicRenderer/BasicTexture2DRenderer.h"

#include "AthanahCommonLib/SupComModelFactory.h"
#include "AthanahCommonLib/UiTextureFactory.h"
#include "AthanahCommonLib/Blueprint/BlueprintFactory.h"
#include "AthanahCommonLib/Blueprint/Blueprint.h"
#include "AthanahCommonLib/Blueprint/BlueprintGeneral.h"

UnitModelSelection::UnitModelSelection(const std::string path, Iyathuum::glmAABB<2> area, std::function<void()> disableAllCall, Graphic& graphic) : _graphic(graphic)
 {
  _disableAllCall = disableAllCall;

  _factory    = std::make_shared<Athanah::SupComModelFactory>(path + "\\units");
  _blueprints = std::make_shared<Athanah::BlueprintFactory  >(path + "\\units");
  _icons      = std::make_shared<Athanah::UiTextureFactory  >(path);
  
  _list = std::make_unique<ListSelection>(_factory->getAvailableModels(), getNames(), area, _graphic.getWindow() , [this](std::string newModel) {
    _currentID = newModel;

    _graphic.setModel(getCurrentModel());

  }, [this](Iyathuum::glmAABB<2> loc, std::string name, bool hovered) {
    drawIcons(loc, name, hovered);
  });
}

void UnitModelSelection::drawIcons(Iyathuum::glmAABB<2> location, std::string name, bool hovered) {
  auto bp = _blueprints->loadModel(name);

  _graphic.getWindow()->renderer().rectangle().start();
  _graphic.getWindow()->renderer().rectangle().drawRectangle(location, hovered ? Iyathuum::Color(0.8f * 255, 0.8f * 255, 0.8f * 255) : Iyathuum::Color(0.4f * 255, 0.4f * 255, 0.4f * 255));
  _graphic.getWindow()->renderer().rectangle().end();

  _graphic.getWindow()->renderer().texture().start();

  auto icon = _icons->getIcon(name);
  location.setSize(glm::vec2(location.getSize()[1], location.getSize()[1]));
  _graphic.getWindow()->renderer().texture().draw(*_icons->getBackgroundIcon(bp->general().icon(),hovered? Athanah::ButtonStatus::Hover:Athanah::ButtonStatus::Normal), location);
  _graphic.getWindow()->renderer().texture().draw(*icon, location);
  Iyathuum::glmAABB<2> factionIconLoc(location.getPosition() + glm::vec2(location.getSize()[0],0), glm::vec2(20, 20));
  _graphic.getWindow()->renderer().texture().draw(*_icons->getFactionIcon(bp->general().faction(), Athanah::FactionIconType::Normal), factionIconLoc);
  Iyathuum::glmAABB<2> stratIconLoc(location.getPosition() + glm::vec2(location.getSize()[0],location.getSize()[1]-20), glm::vec2(20, 20));
  _graphic.getWindow()->renderer().texture().draw(*_icons->getStrategicIcon(bp->strategicIcon(), Athanah::SelectableButtonStatus::Normal), stratIconLoc);

  _graphic.getWindow()->renderer().texture().end();
  _graphic.getWindow()->renderer().text().start();

  std::string text = bp->description() + "\n" + bp->general().unitName();

  _graphic.getWindow()->renderer().text().drawText(text,location.getPosition() + glm::vec2(location.getSize()[0] + 20,0),0.3f);

  _graphic.getWindow()->renderer().text().end();


}

std::shared_ptr<Athanah::SupComModel> UnitModelSelection::getCurrentModel() {
  return _factory->loadModel(_currentID);
}

void UnitModelSelection::setVisible(bool value) {
  _list->setVisible(value);
}

bool UnitModelSelection::isVisible() {
  return _list->isVisible();
}

void UnitModelSelection::update() {
}

void UnitModelSelection::draw() {
  _list->draw();
}

std::vector<std::string> UnitModelSelection::getNames() {
  std::vector<std::string> names;

  for (auto x : _factory->getAvailableModels()) {
    auto bp = _blueprints->loadModel(x);
    names.push_back(bp->description() + "\n" + bp->general().unitName());
  }
  return names;
}
