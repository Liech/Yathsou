#pragma once

#include <memory>

#include "IyathuumCoreLib/lib/glm/glm.hpp"

namespace Iyathuum {
  struct Color;
}

namespace Ahwassa {
  class Camera;

  class BasicBoxRenderer {
  public:
    BasicBoxRenderer(std::shared_ptr<Camera>);
    void start();
    void end();

    void drawLine(glm::vec3 start, glm::vec3 end, float thickness, Iyathuum::Color color);
    void drawDot (glm::vec3 start, glm::vec3 size                , Iyathuum::Color color);
    void drawDot (glm::vec3 start, float     size                , Iyathuum::Color color);
    void drawBox (glm::vec3 start, glm::vec3 size                , Iyathuum::Color color);
    void draw    (glm::mat4 mat                                  , Iyathuum::Color color);
  private:
    struct RenderVars;
    std::shared_ptr<RenderVars> _vars;
  };
}