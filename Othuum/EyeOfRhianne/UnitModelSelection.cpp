#include "UnitModelSelection.h"

#include "ListSelection.h"
#include "AnimationSelection.h"

#include <IyathuumCoreLib/lib/glm/gtc/matrix_transform.hpp>

#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Core/Renderer.h"
#include "AhwassaGraphicsLib/Widgets/Button.h"
#include "AhwassaGraphicsLib/BasicRenderer/BasicTextRenderer.h"

#include "AthanahCommonLib/SupComModelFactory.h"
#include "AthanahCommonLib/BlueprintFactory.h"
#include "AthanahCommonLib/Blueprint.h"
#include "AthanahCommonLib/BlueprintGeneral.h"

UnitModelSelection::UnitModelSelection(const std::string path, std::function<void(std::string)> onUnitChanged, Ahwassa::Window* w) {
  _window = w;
  _onUnitChanged = onUnitChanged;
  _showHide = std::make_unique<Ahwassa::Button>("Units", Iyathuum::glmAABB<2>(glm::vec2(0, w->getHeight() - 50), glm::vec2(300, 50)), [&]() {
    setVisible(!isVisible());
  }, w);
  _factory    = std::make_unique<Athanah::SupComModelFactory>(path);
  _blueprints = std::make_unique<Athanah::BlueprintFactory  >(path);
  
  _animations = std::make_shared<AnimationSelection>(w);

  Iyathuum::glmAABB<2> saveArea(glm::vec2(300, _window->getHeight() - 50), glm::vec2(150, 50));
  Iyathuum::glmAABB<2> unitListArea(glm::vec2(0, 50), glm::vec2(300, w->getHeight() - 100));
  _list = std::make_unique<ListSelection>(_factory->getAvailableModels(), getNames(), unitListArea, w, [this](std::string newModel) {
    _currentID = newModel;
    _animations->setModel(getCurrentModel());
    _onUnitChanged(newModel);
  });
}

std::shared_ptr<Athanah::SupComModel> UnitModelSelection::getCurrentModel() {
  return _factory->loadModel(_currentID);
}

void UnitModelSelection::setVisible(bool value) {
  _list->setVisible(value);
  _animations->setVisible(value);
}

bool UnitModelSelection::isVisible() {
  return _list->isVisible();
}

void UnitModelSelection::update() {
  _animations->update();
}

void UnitModelSelection::draw() {
  _list->draw();
  _showHide->draw();
  _animations->draw();

  if (_currentID.size() > 0) {
    auto bp = _blueprints->loadModel(_currentID);
    _window->renderer().text().start();
    std::string text = bp->general().faction() + "\n" + bp->general().techLevelString();
    glm::vec2 textSize = _window->renderer().text().getTextSize(text, 1);
    _window->renderer().text().drawText(text, glm::vec2(_window->getWidth() - textSize[0], textSize[1]), 1);
    _window->renderer().text().end();
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

std::vector<glm::mat4> UnitModelSelection::getAnimation() {
  return _animations->getAnimation();
}
