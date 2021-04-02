#include "UIElement.h"

namespace Ahwassa {

  void UIElement::setParent(std::shared_ptr<UIElement> parent) {
    _parent = parent;
  }

  std::shared_ptr<UIElement> UIElement::getParent() const {
    return _parent.lock();
  }

  bool UIElement::isVisible() const {
    return _visible; 
  }

  const Iyathuum::glmAABB<2>& UIElement::getLocalPosition() const{
    return _localPosition;
  }

  const Iyathuum::glmAABB<2> UIElement::getGlobalPosition() const {
    Iyathuum::glmAABB<2> result = _localPosition;
    auto parent = _parent.lock();
    if (parent)
      result.setPosition(glm::vec2(
        result.getPosition()[0] + parent->getGlobalPosition().getPosition()[0],
        result.getPosition()[1] + parent->getGlobalPosition().getPosition()[1]));
    return result;
  }

  void UIElement::setLocalPosition(Iyathuum::glmAABB<2> pos) {
    _localPosition = pos;
  }
}