#pragma once

#include <iostream>
#include "IyathuumCoreLib/Singleton/Factory.h"
#include "IyathuumCoreLib/lib/glm/glm.hpp"
#include "IyathuumCoreLib/BaseTypes/glmAABB.h"
#include "IyathuumCoreLib/BaseTypes/Color.h"
#include <memory>

#include <map>

namespace Ahwassa {
  class Window;

  class BasicRectangleRenderer {
  public:
    BasicRectangleRenderer(Window*);
    virtual ~BasicRectangleRenderer() {}
    void start();
    void end();
    void drawRectangle(const glm::vec2& pos, const glm::vec2& size, const Iyathuum::Color& color);
    void drawRectangle(const Iyathuum::glmAABB<2>& box, const Iyathuum::Color& color);
    void drawDot(const glm::vec2& pos, float size, const Iyathuum::Color& color);
    void drawLine(const glm::vec2& posA, const glm::vec2& posB, float thicknessPx, const Iyathuum::Color& color);
    void drawCircle(const glm::vec2& center, const glm::vec2& radius, float rotation, float thickness, const Iyathuum::Color&, float precision = 5);
    void setClippingRectangle(const Iyathuum::glmAABB<2>& box);
    void disableClipping();
    void setResolution(const glm::ivec2& resolution);
  private:
    struct RenderVars;

    void makeShader();

    glm::ivec2           _resolution;
    bool                 _inRenderProcess = false;
    bool                 _clipping        = false;
    Iyathuum::glmAABB<2> _clippingBox;
    std::shared_ptr<RenderVars>           _vars;
  };
}
