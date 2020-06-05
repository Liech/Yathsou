#include "ListLayout.h"
#include "../../Renderer/RectangleRenderer.h"
#include "../../Renderer/TextRenderer.h"
#include "IyathuumCoreLib/Util/Geometry.h"
#include "Drawables/Widgets/Button.h"
#include "Drawables/Widgets/Label.h"
#include "Drawables/Widgets/LineEdit.h"
#include "IyathuumCoreLib/Singleton/Database.h"

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

      RectangleRenderer::setClippingRectangle(getGlobalPosition());
      TextRenderer::setClippingRectangle(getGlobalPosition());

      RectangleRenderer::start();
      RectangleRenderer::drawRectangle(getGlobalPosition(), glm::vec3(0.7f, 0.7f, 0.7f));
      RectangleRenderer::end();

      for (auto w : _widgets) {
        w->draw();
      }

      RectangleRenderer::disableClipping();
      TextRenderer::disableClipping();

      float scrollMax = getMaximumScroll();
      float current   = getCurrentScroll();
      if (scrollMax > 0) {
        RectangleRenderer::start();
        Iyathuum::AABB<2> scrollBar;
        float y = getGlobalPosition().getPosition()[1];
        float x = getGlobalPosition().getPosition()[0] + getGlobalPosition().getSize()[0];
        float maxY = getGlobalPosition().getSize()[1];
        float height = 30;
        scrollBar.setPosition({x-10,y + (maxY-height)*current/scrollMax});
        scrollBar.setSize({ 10, height });
        RectangleRenderer::drawRectangle(scrollBar, glm::vec3(0.7f, 0.0f, 0.7f));
        RectangleRenderer::end();
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
      std::shared_ptr<Widgets::Label> l = std::make_shared<Widgets::Label>(text, getElementSize(),this);
      addWidget(l);
      return l;
    }

    std::shared_ptr<Widgets::LineEdit> ListLayout::addLineEdit(std::string text) {
      std::shared_ptr<Widgets::LineEdit> l = std::make_shared<Widgets::LineEdit>(text, getElementSize(), this);
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

      if (visible && !isVisible())
        Iyathuum::Database<Widgets::Widget*>::add(this, { "MouseWheel" });
      else if (!visible && isVisible())
        Iyathuum::Database<Widgets::Widget*>::remove(this);

      Widget::setVisible(visible);
    }

    std::vector<std::shared_ptr<Widget>> ListLayout::getWidgets() {
      return _widgets;
    }

    std::array<double, 2> ListLayout::getPotentialSize() {
      double maxOffset = 0;
      if (!_horizontal)
        for (auto w : _widgets)
          maxOffset += w->getPosition().getSize()[1];
      double offset = _horizontal ? 0 : maxOffset;
      double max = 0;
      for (auto w : _widgets) {
        if (!_horizontal) {
          offset -= w->getPosition().getSize()[1];
          max = std::max(max, w->getPosition().getSize()[0]);
        }
        else {
          max = std::max(max, w->getPosition().getSize()[1]);
          offset += w->getPosition().getSize()[0];
        }
      }
      std::array<double, 2> siz;
      if (_horizontal)
        siz = std::array<double, 2>{offset, max};
      else
        siz = std::array<double, 2>{max, maxOffset};
      return siz;
    }

    void ListLayout::adjustSize(){
      double maxOffset = 0;
      if (!_horizontal)
        for (auto w : _widgets)
          maxOffset += w->getPosition().getSize()[1];
      double offset = _horizontal ? 0 : maxOffset;
      double max = 0;
      for (auto w : _widgets) {
        w->adjustSize();

        if (!_horizontal) {
          offset -= w->getPosition().getSize()[1];
          w->getPosition().setPosition(std::array<double, 2>{0, offset - _scroll});
          max = std::max(max, w->getPosition().getSize()[0]);
        }
        else {
          w->getPosition().setPosition(std::array<double, 2>{offset - _scroll, 0});
          max = std::max(max, w->getPosition().getSize()[1]);
          offset += w->getPosition().getSize()[0];
        }
      }
      std::array<double, 2> siz;
      if (_horizontal)
        siz = std::array<double, 2>{offset, max};
      else
        siz = std::array<double, 2>{max, maxOffset};
      if (_maximumSize[0] != 0)
        siz[0] = std::clamp(siz[0], 0.0, (double)_maximumSize[0]);
      if (_maximumSize[1] != 0)
        siz[1] = std::clamp(siz[1], 0.0, (double)_maximumSize[1]);
      getPosition().setSize(siz);
    }

    float ListLayout::getMaximumScroll() {
      float potential;
      if (_horizontal)
        potential = getPotentialSize()[0];
      else
        potential = getPotentialSize()[1];
      float maximum = _horizontal ? _maximumSize[0] : _maximumSize[1];
      if (maximum == 0)
        return 0;
      if (potential < maximum) 
        return 0;
      return potential - maximum;
    }
    
    bool ListLayout::mouseWheel(glm::vec2 movement) {
      float max = getMaximumScroll();
      if (max > 0) {
        setCurrentScroll(std::clamp(getCurrentScroll() + movement[1]*5, 0.0f, max));
        return true;
      }
      return false;
    }
  }
}