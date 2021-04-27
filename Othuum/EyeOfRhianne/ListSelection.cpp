#include "ListSelection.h"
#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Widgets/ListLayout.h"
#include "AhwassaGraphicsLib/Widgets/Button.h"
#include "IyathuumCoreLib/BaseTypes/glmAABB.h"

ListSelection::ListSelection(const std::vector<std::string>& options, const std::vector<std::string>& names, Iyathuum::glmAABB<2> loc, Ahwassa::Window* window, std::function<void(std::string)> onClick) {
  _onClick = onClick;
  _window = window;
  _options = options;
  _names = names;
  _location = loc;
  init();
}

ListSelection::ListSelection(const std::vector<std::string>& options, const std::vector<std::string>& names, Iyathuum::glmAABB<2> loc, Ahwassa::Window* window, std::function<void(std::string)> onClick, std::function<void(Iyathuum::glmAABB<2>, std::string,bool)> overrideDraw) {
  _onClick = onClick;
  _window = window;
  _options = options;
  _names = names;
  _location = loc;
  _overrideDraw = overrideDraw;
  _overrideEnabled = true;
  init();
}

void ListSelection::init() {
  _layout = std::make_shared<Ahwassa::ListLayout>(_location, _window);
  _layout->setMaximumSize(_location.getSize());
  for (int i = 0; i < _options.size(); i++) {
    auto b = _layout->addButton(_names[i], [this, i]() { _onClick(_options[i]); });
    if (_overrideEnabled)
      b->setDrawOverride([this,i](Iyathuum::glmAABB<2> loc, bool hovered) {
      _overrideDraw(loc, _options[i], hovered);
    });
    b->setTextSize(0.5f);
  }
  _layout->adjustSize();
  _layout->setCurrentScroll(_layout->getMaximumScroll());
}

void ListSelection::draw() {
  _layout->adjustSize();
  _layout->draw();
}

void ListSelection::setVisible(bool visible) {
  _layout->setVisible(visible);
}

bool ListSelection::isVisible() {
  return _layout->isVisible();
}
