#include "CircleShape.h"  

#include "AhwassaGraphicsLib/BasicRenderer/BasicRectangleRenderer.h"

namespace Superb {
  namespace Formation {
    void CircleShape::draw(Ahwassa::BasicRectangleRenderer& renderer) {
      renderer.drawCircle(getPosition().getCenter(), getPosition().getSize() / 2.0f, 0, 2, Iyathuum::Color(255, 0, 0));
    }
  }
}