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
  _layout->adjustSize();
  _layout->setPosition(getAABB());
  _layout->draw();
}

Iyathuum::AABB<2> DialogPage::getAABB() {
  if (_layout == nullptr)
    return Iyathuum::AABB<2>(std::array<double, 2>{ 0.0,0.0 }, std::array<double, 2>{ (double)_width/2,(double)_height/2 });
  Iyathuum::AABB<2> result;
  auto size = _layout->getPosition().getSize();
  result.setPosition(std::array<double, 2>{ (_width / 2.0 - size[0] / 2.0), _height / 2.0 - size[1]/2.0});
  return result;
}

void DialogPage::setVisible(bool visible) {
  _layout->setVisible(visible);
  _visible = visible; 
}

YolonaOss::Widgets::ListLayout& DialogPage::layout() {
  return *_layout;
}
