#include "Widget.h"

namespace YolonaOss {
  namespace Widgets {

    BoundingBox2 Widget::getPosition() const {
      return _position;
    }

    void Widget::setPosition(BoundingBox2 pos) {
      _position = pos;
    }
  }
}