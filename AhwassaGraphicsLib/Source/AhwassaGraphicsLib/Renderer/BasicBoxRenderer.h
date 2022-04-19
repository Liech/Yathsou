#pragma once

#include <memory>

#include <glm/glm.hpp>

namespace Iyathuum {
  class Color;
}

namespace Ahwassa {
  class Camera;

  class BasicBoxRenderer {
  public:
    BasicBoxRenderer(std::shared_ptr<Camera>);
    void start();
    void end();

    void drawLine(const glm::vec3& start, const glm::vec3& end, float thickness, const Iyathuum::Color& color);
    void drawDot (const glm::vec3& start, const glm::vec3& size                , const Iyathuum::Color& color);
    void drawDot (const glm::vec3& start, float     size                       , const Iyathuum::Color& color);
    void drawBox (const glm::vec3& start, const glm::vec3& size                , const Iyathuum::Color& color);
    void draw    (const glm::mat4& mat                                         , const Iyathuum::Color& color);
  private:
    struct RenderVars;
    std::shared_ptr<RenderVars> _vars;
  };
}