#include "TriangleShape.h"  

#include "AhwassaGraphicsLib/BasicRenderer/BasicRectangleRenderer.h"

namespace Superb {
  namespace Formation {
    void TriangleShape::draw(Ahwassa::BasicRectangleRenderer& renderer) {
      renderer.drawCircle(getPosition().getCenter(), getPosition().getSize() / 2.0f, 0, 2, Iyathuum::Color(255, 0, 0));
      const auto& pos = getPosition();
      glm::vec2 a = pos.getPosition() + glm::vec2(pos.getSize()[0] / 2.0f,0);
      glm::vec2 b = pos.getPosition() + glm::vec2(0, pos.getSize()[1]);
      glm::vec2 c = pos.getPosition() + pos.getSize();
      renderer.drawLine(a, b, 1, Iyathuum::Color(255, 0, 0));
      renderer.drawLine(b, c, 1, Iyathuum::Color(255, 0, 0));
      renderer.drawLine(c, a, 1, Iyathuum::Color(255, 0, 0));
    }
  }
}