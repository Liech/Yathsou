#include "Widget.h"

namespace YolonaOss {
  namespace Widgets {

    Iyathuum::AABB<2>& Widget::getPosition() {
      return _position;
    }

    Iyathuum::AABB<2> Widget::getGlobalPosition() const {
      Iyathuum::AABB<2> result = _position;
      if (_parent != nullptr)
        result.setPosition(std::array<double, 2>{result.getPosition()[0] + _parent->getGlobalPosition().getPosition()[0],
                                                 result.getPosition()[1] + _parent->getGlobalPosition().getPosition()[1]});
      return result;
    }

    void Widget::setPosition(Iyathuum::AABB<2> pos) {
      _position = pos;
    }
    
    void Widget::setVisible(bool visible) {
      _visible = visible;
    }


  }
}