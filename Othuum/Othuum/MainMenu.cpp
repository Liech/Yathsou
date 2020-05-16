#include "MainMenu.h"

#include "YolonaOss/Drawables/Widgets/ListLayout.h"

MainMenu::MainMenu(int width, int height) {
  _width  = width ;
  _height = height;
  _layout = std::make_unique<YolonaOss::Widgets::ListLayout>(getAABB());
}

void MainMenu::load(YolonaOss::GL::DrawSpecification* spec)
{
  _layout->load(spec);
}

void MainMenu::draw()
{  
  for (auto w : _buttons)
    w->setPosition(Iyathuum::AABB<2>(std::array<double, 2> {0.0,0.0}, std::array<double, 2> {(double)buttonWidth,(double)buttonHeight}));
  _layout->setPosition(getAABB());
  _layout->draw();
}

void MainMenu::addButton(std::string name, std::function<void()> onClicked) {
  _buttons.push_back(_layout->addButton(name, onClicked));
}

Iyathuum::AABB<2> MainMenu::getAABB() {
  Iyathuum::AABB<2> result;
  result.setPosition(std::array<double, 2>{ (_width / 2.0 - buttonWidth / 2.0), _height / 2.0 - buttonHeight* _buttons.size() /2.0});
  result.setSize(std::array<double, 2> {(double)buttonWidth, (double)buttonHeight* _buttons.size()});
  return result;
}
