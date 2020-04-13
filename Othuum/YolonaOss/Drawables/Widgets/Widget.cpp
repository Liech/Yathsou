#include "Widget.h"

namespace YolonaOss {
  namespace Widgets {

    Iyathuum::AABB<2> Widget::getPosition() const {
      return _position;
    }

    void Widget::setPosition(Iyathuum::AABB<2> pos) {
      _position = pos;
    }
  }
}