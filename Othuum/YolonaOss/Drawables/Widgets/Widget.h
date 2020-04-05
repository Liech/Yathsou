#pragma once

#include "../../OpenGL/Drawable.h"
#include "../../OpenGL/Keys.h"
#include "../..//structs/BoundingBox.h"

namespace YolonaOss {
  namespace Widgets {
    class Widget : public GL::Drawable {
    public:
      Widget(BoundingBox2 position) {
        _position = position;
      }
      Widget() {
        _position = BoundingBox2(glm::vec2(0, 0), glm::vec2(100, 100));
      }

      virtual ~Widget() {};

      virtual void mouseEnter() {};
      virtual void mouseLeave() {};
      virtual void mouseClick(glm::vec2 position, GL::Key k) {};
      virtual void mouseMove(glm::vec2 position) {};

      BoundingBox2 getPosition() const;
      void setPosition(BoundingBox2 pos);
    private:
      BoundingBox2 _position;
    };
  }
}