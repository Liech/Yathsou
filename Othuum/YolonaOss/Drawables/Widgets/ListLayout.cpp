#include "ListLayout.h"
#include "../../Renderer/RectangleRenderer.h"
#include "IyathuumCoreLib/Util/Geometry.h"
#include "Drawables/Widgets/Button.h"
#include "Drawables/Widgets/Label.h"

namespace YolonaOss {
  namespace Widgets {
    ListLayout::ListLayout(Iyathuum::AABB<2> position, Widget* parent) : Widget(position, parent){
      setVisible(true);
    }

    int  ListLayout::addWidget(std::shared_ptr<Widget> w) {
      _widgets.push_back(w);
      return (int)(_widgets.size() - 1);
    }

    void ListLayout::removeWidget(int w) {
      _widgets.erase(_widgets.begin() + w);
    }

    void ListLayout::draw() {
      if (!isVisible())
        return;

      RectangleRenderer::start();
      RectangleRenderer::drawRectangle(getGlobalPosition(), glm::vec3(0.7f, 0.7f, 0.7f));
      RectangleRenderer::end();

      for (auto w : _widgets) {
        w->draw();
      }
    }
    
    void ListLayout::setHorizontal(bool horizontal) {
      _horizontal = horizontal;
    }

    std::shared_ptr<Widgets::Button> ListLayout::addButton(std::string name, std::function<void()> onClicked, Iyathuum::AABB<2> size) {
      std::shared_ptr<Widgets::Button> b = std::make_shared<Widgets::Button>(name, getElementSize(), [onClicked]() { onClicked(); },this);
      addWidget(b);
      return b;
    }

    std::shared_ptr<Widgets::ListLayout> ListLayout::addLayout() {
      std::shared_ptr<Widgets::ListLayout> l = std::make_shared<Widgets::ListLayout>(getElementSize(),this);
      addWidget(l);
      return l;
    }

    std::shared_ptr<Widgets::Label> ListLayout::addLabel(std::string text){
      std::shared_ptr<Widgets::Label> l = std::make_shared<Widgets::Label>(text, getElementSize());
      addWidget(l);
      return l;
    }

    Iyathuum::AABB<2> ListLayout::getElementSize() {
      //if (!_horizontal)
        return Iyathuum::AABB<2>(std::array<double, 2>{ 0.0, 0.0 }, std::array<double, 2>{ getPosition().getSize()[0], 50.0 });
      //else
        //return Iyathuum::AABB<2>(std::array<double, 2>{ 0.0, 0.0 }, std::array<double, 2>{ 50.0 , getPosition().getSize()[0]});
    }

    void ListLayout::setVisible(bool visible) {
      for (auto w : _widgets)
        w->setVisible(visible);

      Widget::setVisible(visible);
    }

    std::vector<std::shared_ptr<Widget>> ListLayout::getWidgets() {
      return _widgets;
    }

    void ListLayout::adjustSize(){
      double maxOffset = 0;
      if (!_horizontal)
        for (auto w : _widgets)
          maxOffset += w->getPosition().getSize()[1];
      double offset = _horizontal?0:maxOffset;
      double max = 0;
      for (auto w : _widgets) {
        w->adjustSize();

        if (!_horizontal) {
          w->getPosition().setPosition(std::array<double, 2>{0,offset});
          max = std::max(max,w->getPosition().getSize()[0]);
          offset -= w->getPosition().getSize()[1];
        }
        else {
          w->getPosition().setPosition(std::array<double, 2>{offset,0});
          max = std::max(max,w->getPosition().getSize()[1]);
          offset += w->getPosition().getSize()[0];
        }         
      }
      if (_horizontal)
        getPosition().setSize(std::array<double, 2>{offset, max});
      else
        getPosition().setSize(std::array<double, 2>{max, maxOffset});
    }

  }
}