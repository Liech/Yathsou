#include "TriangleShape.h"  

#include "AhwassaGraphicsLib/Renderer/BasicRectangleRenderer.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Superb {
  namespace Formation {
    void TriangleShape::draw(Ahwassa::BasicRectangleRenderer& renderer) {
      const auto& pos = getPosition();
      glm::vec2 a = pos.getPosition() + glm::vec2(pos.getSize()[0] / 2.0f,0);
      glm::vec2 b = pos.getPosition() + glm::vec2(0, pos.getSize()[1]);
      glm::vec2 c = pos.getPosition() + pos.getSize();

      glm::vec3 center = glm::vec3(pos.getCenter()[0], pos.getCenter()[1], 0);
      glm::mat4 rotation = glm::translate(glm::mat4(1.0), center);
      rotation = glm::rotate(rotation, glm::radians(getRotation()), glm::vec3(0, 0, 1));
      rotation = glm::translate(rotation, -center);

      glm::vec4 ar = rotation * glm::vec4(a[0], a[1], 0, 1);
      glm::vec4 br = rotation * glm::vec4(b[0], b[1], 0, 1);
      glm::vec4 cr = rotation * glm::vec4(c[0], c[1], 0, 1);

      renderer.drawLine(glm::vec2(ar[0], ar[1]), glm::vec2(br[0], br[1]), 1, Iyathuum::Color(255, 0, 0));
      renderer.drawLine(glm::vec2(br[0], br[1]), glm::vec2(cr[0], cr[1]), 1, Iyathuum::Color(255, 0, 0));
      renderer.drawLine(glm::vec2(cr[0], cr[1]), glm::vec2(ar[0], ar[1]), 1, Iyathuum::Color(255, 0, 0));
      FormationShape::draw(renderer);
    }
  }
}