#include "UnitModelSelection.h"

#include "ListSelection.h"
#include "Graphic.h"


#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Core/Renderer.h"
#include "AhwassaGraphicsLib/Widgets/Button.h"
#include "AhwassaGraphicsLib/BasicRenderer/BasicTextRenderer.h"

#include "AthanahCommonLib/SupComModelFactory.h"
#include "AthanahCommonLib/BlueprintFactory.h"
#include "AthanahCommonLib/Blueprint.h"
#include "AthanahCommonLib/BlueprintGeneral.h"

UnitModelSelection::UnitModelSelection(const std::string path, Iyathuum::glmAABB<2> area, std::function<void()> disableAllCall, Graphic& graphic) : _graphic(graphic)
 {
  _disableAllCall = disableAllCall;

  _factory    = std::make_shared<Athanah::SupComModelFactory>(path);
  _blueprints = std::make_shared<Athanah::BlueprintFactory  >(path);
  
  _list = std::make_unique<ListSelection>(_factory->getAvailableModels(), getNames(), area, _graphic.getWindow() , [this](std::string newModel) {
    _currentID = newModel;

    _graphic.setModel(getCurrentModel());

  });
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

  if (_currentID.size() > 0) {
    auto bp = _blueprints->loadModel(_currentID);
    _graphic.getWindow()->renderer().text().start();
    std::string text = bp->general().faction() + "\n" + bp->general().techLevelString();
    glm::vec2 textSize = _graphic.getWindow()->renderer().text().getTextSize(text, 1);
    _graphic.getWindow()->renderer().text().drawText(text, glm::vec2(_graphic.getWindow()->getWidth() - textSize[0], textSize[1]), 1);
    _graphic.getWindow()->renderer().text().end();
  }
}

std::vector<std::string> UnitModelSelection::getNames() {
  std::vector<std::string> names;

  for (auto x : _factory->getAvailableModels()) {
    auto bp = _blueprints->loadModel(x);
    names.push_back(bp->description() + "\n" + bp->general().unitName());
  }
  return names;
}
