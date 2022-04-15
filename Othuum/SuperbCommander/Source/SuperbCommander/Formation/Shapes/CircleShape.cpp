#include "CircleShape.h"  

#include "AhwassaGraphicsLib/Renderer/BasicRectangleRenderer.h"

namespace Superb {
  namespace Formation {
    void CircleShape::draw(Ahwassa::BasicRectangleRenderer& renderer) {
      renderer.drawCircle(getPosition().getCenter(), getPosition().getSize() / 2.0f, getRotation(), 2, Iyathuum::Color(255, 0, 0));
      FormationShape::draw(renderer);
    }
  }
}