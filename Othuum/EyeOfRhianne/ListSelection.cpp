#include "ListSelection.h"
#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Widgets/ListLayout.h"
#include "AhwassaGraphicsLib/Widgets/Button.h"
#include "IyathuumCoreLib/BaseTypes/glmAABB.h"

ListSelection::ListSelection(const std::vector<std::string>& options, Iyathuum::glmAABB<2> loc, Ahwassa::Window* window, std::function<void(std::string)> onClick){
  _onClick = onClick;
  _window = window;
  _options = options;

  _layout = std::make_shared<Ahwassa::ListLayout>(loc,_window);
  _layout->setMaximumSize(loc.getSize());
  for (int i = 0; i < _options.size(); i++) {
    auto b = _layout->addButton(_options[i], [this, i]() { _onClick(_options[i]); });
    b->setTextSize(0.5f);
  }
  _layout->adjustSize();
  _layout->setCurrentScroll(_layout->getMaximumScroll());
}

void ListSelection::draw() {
  _layout->adjustSize();
  _layout->draw();
}
