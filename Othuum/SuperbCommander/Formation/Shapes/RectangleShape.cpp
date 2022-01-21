#include "RectangleShape.h"  

#include "AhwassaGraphicsLib/BasicRenderer/BasicRectangleRenderer.h"

namespace Superb {
  namespace Formation {
    void RectangleShape::draw(Ahwassa::BasicRectangleRenderer& renderer) {
      const auto& pos = getPosition();
      glm::vec2 a = pos.getPosition();
      glm::vec2 b = pos.getPosition() + glm::vec2(pos.getSize()[0], 0);
      glm::vec2 c = pos.getPosition() + pos.getSize()[0];
      glm::vec2 d = pos.getPosition() + glm::vec2(0, pos.getSize()[1]);
      renderer.drawLine(a, b, 1, Iyathuum::Color(255, 0, 0));
      renderer.drawLine(b, c, 1, Iyathuum::Color(255, 0, 0));
      renderer.drawLine(c, d, 1, Iyathuum::Color(255, 0, 0));
      renderer.drawLine(d, a, 1, Iyathuum::Color(255, 0, 0));
    }
  }
}