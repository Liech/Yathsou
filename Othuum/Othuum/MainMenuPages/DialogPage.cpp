#include "DialogPage.h"

#include "AhwassaGraphicsLib/Widgets/ListLayout.h"
#include "AhwassaGraphicsLib/Core/Window.h"

DialogPage::DialogPage(Ahwassa::Window* w) : Ahwassa::Drawable(w) {
  _layout = std::make_unique<Ahwassa::ListLayout>(getAABB(),w);
}

void DialogPage::draw()
{  
  if (!_visible)
    return;
  _layout->adjustSize();
  _layout->setLocalPosition(getAABB());
  _layout->draw();
}

Iyathuum::glmAABB<2> DialogPage::getAABB() {
  if (_layout == nullptr)
    return Iyathuum::glmAABB<2>({ 0.0,0.0 }, { getWindow()->getHeight()/2,getWindow()->getHeight()/2 });
  Iyathuum::glmAABB<2> result;
  _layout->adjustSize();
  auto size = _layout->getLocalPosition().getSize();
  result.setPosition({ (getWindow()->getHeight() / 2.0 - size[0] / 2.0), getWindow()->getHeight() / 2.0 - size[1]/2.0});
  result.setSize(size);
  return result;
}

void DialogPage::setVisible(bool visible) {
  _layout->setVisible(visible);
  _visible = visible; 
}

Ahwassa::ListLayout& DialogPage::layout() {
  return *_layout;
}
