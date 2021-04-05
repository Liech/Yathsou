#include "ListLayout.h"

#include "IyathuumCoreLib/Singleton/Database.h"
#include "BasicRenderer/BasicRectangleRenderer.h"
#include "BasicRenderer/BasicTextRenderer.h"
#include "Core/Window.h"
#include "Core/Renderer.h"

#include "Button.h"
#include "Slider.h"
#include "Label.h"
#include "LineEdit.h"


namespace Ahwassa {
  ListLayout::ListLayout(Iyathuum::glmAABB<2> position, Window* w, UIElement* parent) : Drawable(w) {
    setLocalPosition(position);
    setParent(parent);
  }

  void ListLayout::clear() {
    _widgets.clear();
  }

  int  ListLayout::addElement(std::shared_ptr<UIElement> w) {
    w->setParent(this);
    _widgets.push_back(w);
    return (int)(_widgets.size() - 1);
  }

  void ListLayout::removeWidget(int w) {
    _widgets.erase(_widgets.begin() + w);
  }

  std::shared_ptr<Button> ListLayout::addButton(std::string name, std::function<void()> onClicked, Iyathuum::glmAABB<2> size) {
    std::shared_ptr<Button> b = std::make_shared<Button>(name, getElementSize(), [onClicked]() { onClicked(); },getWindow(),this);
    addElement(b);
    return b;
  }

  std::shared_ptr<ListLayout> ListLayout::addLayout() {
    std::shared_ptr<ListLayout> l = std::make_shared<ListLayout>(getElementSize(),getWindow(),this);
    addElement(l);
    return l;
  }

  std::shared_ptr<Label> ListLayout::addLabel(std::string text){
    std::shared_ptr<Label> l = std::make_shared<Label>(text, getElementSize(),getWindow(),this);
    addElement(l);
    return l;
  }

  std::shared_ptr<LineEdit> ListLayout::addLineEdit(std::string text) {
    std::shared_ptr<LineEdit> l = std::make_shared<LineEdit>(text, getElementSize(),getWindow(), this);
    addElement(l);
    return l;

  }

  void ListLayout::draw() {
    if (!isVisible())
      return;

    getWindow()->renderer().rectangle().setClippingRectangle(getGlobalPosition());
    getWindow()->renderer().text().setClippingRectangle(getGlobalPosition());

    getWindow()->renderer().rectangle().start();
    getWindow()->renderer().rectangle().drawRectangle(getGlobalPosition(), Iyathuum::Color(255*0.7f, 255 * 0.7f, 255 * 0.7f));
    getWindow()->renderer().rectangle().end();

    for (auto w : _widgets) {
      w->draw();
    }

    getWindow()->renderer().rectangle().disableClipping();
    getWindow()->renderer().text().disableClipping();

    float scrollMax = getMaximumScroll();
    float current = getCurrentScroll();
    if (scrollMax > 0) {
      getWindow()->renderer().rectangle().start();
      Iyathuum::glmAABB<2> scrollBar;
      float y = getGlobalPosition().getPosition()[1];
      float x = getGlobalPosition().getPosition()[0] + getGlobalPosition().getSize()[0];
      float maxY = getGlobalPosition().getSize()[1];
      float height = 30;
      scrollBar.setPosition({ x - 10,y + (maxY - height) * current / scrollMax });
      scrollBar.setSize({ 10, height });
      getWindow()->renderer().rectangle().drawRectangle(scrollBar, Iyathuum::Color(255*0.7f, 0.0f, 255*0.7f));
      getWindow()->renderer().rectangle().end();
    }
  }

  void ListLayout::setHorizontal(bool horizontal) {
    _horizontal = horizontal;
  }

  Iyathuum::glmAABB<2> ListLayout::getElementSize() {
    //if (!_horizontal)
    return Iyathuum::glmAABB<2>({ 0.0, 0.0 }, { getLocalPosition().getSize()[0], 50.0 });
    //else
      //return Iyathuum::AABB<2>(std::array<double, 2>{ 0.0, 0.0 }, std::array<double, 2>{ 50.0 , getPosition().getSize()[0]});
  }

  std::vector<std::shared_ptr<UIElement>> ListLayout::getElements() {
    return _widgets;
  }

  std::array<double, 2> ListLayout::getPotentialSize() {
    double maxOffset = 0;
    if (!_horizontal)
      for (auto w : _widgets) {
        if (!w->isVisible())
          continue;
        maxOffset += w->getLocalPosition().getSize()[1];
      }
    float offset = _horizontal ? 0 : maxOffset;
    float max = 0;
    for (auto w : _widgets) {
      if (!w->isVisible())
        continue;
      if (!_horizontal) {
        offset -= w->getLocalPosition().getSize()[1];
        max = std::max(max, w->getLocalPosition().getSize()[0]);
      }
      else {
        max = std::max(max, w->getLocalPosition().getSize()[1]);
        offset += w->getLocalPosition().getSize()[0];
      }
    }
    std::array<double, 2> siz;
    if (_horizontal)
      siz = std::array<double, 2>{offset, max};
    else
      siz = std::array<double, 2>{max, maxOffset};
    return siz;
  }

  void ListLayout::adjustSize() {
    double maxOffset = 0;
    if (!_horizontal)
      for (auto w : _widgets) {
        if (!w->isVisible())
          continue;
        maxOffset += w->getLocalPosition().getSize()[1];
      }
    float offset = _horizontal ? 0 : maxOffset;
    float max = 0;
    for (auto w : _widgets) {
      if (!w->isVisible())
        continue;

      if (!_horizontal) {
        offset -= w->getLocalPosition().getSize()[1];
        w->setLocalPosition(Iyathuum::glmAABB<2>(glm::vec2{ offset - _scroll, 0 }, w->getLocalPosition().getSize()));
        max = std::max(max, w->getLocalPosition().getSize()[0]);
      }
      else {
        w->setLocalPosition(Iyathuum::glmAABB<2>(glm::vec2{ offset - _scroll, 0 },w->getLocalPosition().getSize()));
        max = std::max(max, w->getLocalPosition().getSize()[1]);
        offset += w->getLocalPosition().getSize()[0];
      }
    }
    glm::vec2 siz;
    if (_horizontal)
      siz = glm::vec2{offset, max};
    else
      siz = glm::vec2{max, maxOffset};
    if (_maximumSize[0] != 0)
      siz[0] = std::clamp(siz[0], 0.0f, _maximumSize[0]);
    if (_maximumSize[1] != 0)
      siz[1] = std::clamp(siz[1], 0.0f, _maximumSize[1]);
    setLocalPosition(Iyathuum::glmAABB<2>(getLocalPosition().getPosition(), siz));
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

  bool ListLayout::mouseWheelEvent(glm::vec2 movement) {
    float max = getMaximumScroll();
    if (max > 0) {
      setCurrentScroll(std::clamp(getCurrentScroll() + movement[1] * 5, 0.0f, max));
      return true;
    }
    return false;
  }
}