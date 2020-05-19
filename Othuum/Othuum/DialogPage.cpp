#include "DialogPage.h"

#include "YolonaOss/Drawables/Widgets/ListLayout.h"

DialogPage::DialogPage(int width, int height) {
  _width  = width ;
  _height = height;
  _layout = std::make_unique<YolonaOss::Widgets::ListLayout>(getAABB());
}

void DialogPage::load(YolonaOss::GL::DrawSpecification* spec)
{
  _layout->load(spec);
}

void DialogPage::draw()
{  
  if (!_visible)
    return;
  for (auto w : _layout->getWidgets())
    w->setPosition(Iyathuum::AABB<2>(std::array<double, 2> {0.0,0.0}, std::array<double, 2> {(double)buttonWidth,(double)buttonHeight}));
  _layout->setPosition(getAABB());
  _layout->draw();
}

void DialogPage::addButton(std::string name, std::function<void()> onClicked) {
  _layout->addButton(name, onClicked);
}

Iyathuum::AABB<2> DialogPage::getAABB() {
  if (_layout == nullptr)
    return Iyathuum::AABB<2>();
  Iyathuum::AABB<2> result;
  result.setPosition(std::array<double, 2>{ (_width / 2.0 - buttonWidth / 2.0), _height / 2.0 - buttonHeight* _layout->getWidgets().size() /2.0});
  result.setSize(std::array<double, 2> {(double)buttonWidth, (double)buttonHeight* _layout->getWidgets().size()});
  return result;
}

void DialogPage::setVisible(bool visible) {
  _layout->setVisible(visible);
  _visible = visible; 
}
