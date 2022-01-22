#include "Selector.h"

#include "AhwassaGraphicsLib/BasicRenderer/BasicRectangleRenderer.h"

namespace Superb {
  namespace Formation {
    void Selector::setPosition(const Iyathuum::glmAABB<2>& pos) {
      _position = pos;
    }

    void Selector::draw(Ahwassa::BasicRectangleRenderer& renderer) {
      const float extra = 3;
      const auto p = _position.getPosition() - glm::vec2(extra, extra);
      const auto s = _position.getSize() + glm::vec2(extra*2,extra*2);

      renderer.drawLine(p, p + glm::vec2(10, 0), 3, _color);
      renderer.drawLine(p, p + glm::vec2(0, 10), 3, _color);

      const auto p2 = p + glm::vec2(s[0], 0);
      renderer.drawLine(p2, p2 + glm::vec2(-10, 0), 3, _color);
      renderer.drawLine(p2, p2 + glm::vec2(0, 10), 3 , _color);
      
      const auto p3 = p + glm::vec2(0, s[0]);
      renderer.drawLine(p3, p3 + glm::vec2(10, 0), 3 , _color);
      renderer.drawLine(p3, p3 + glm::vec2(0, -10), 3, _color);
      
      const auto p4 = p + s;
      renderer.drawLine(p4, p4 + glm::vec2(-10, 0), 3, _color);
      renderer.drawLine(p4, p4 + glm::vec2(0, -10), 3, _color);

      if (_selected) {
        const glm::vec2 rotatorPosition = p - glm::vec2(10, 10);
        renderer.drawCircle(rotatorPosition, glm::vec2(5,5), 0, 1, _color);
      }
    }

    void Selector::setSelected(bool sel) {
      _selected = sel;
    }

    void Selector::setColor(const Iyathuum::Color& clr) {
      _color = clr;
    }

    bool Selector::insideRotate(const glm::vec2& mousePos) {
      const float extra = 3;
      const auto p = _position.getPosition() - glm::vec2(extra, extra);
      const glm::vec2 rotatorPosition = p - glm::vec2(10, 10);
      return glm::distance(mousePos, rotatorPosition) < 5;
    }
  }
}