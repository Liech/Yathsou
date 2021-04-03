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

  class RectangleRenderer {
  public:
    RectangleRenderer(Window*);
    virtual ~RectangleRenderer() {}
    void start();
    void end();
    void drawRectangle(glm::vec2 pos, glm::vec2 size, Iyathuum::Color color);
    void drawRectangle(Iyathuum::glmAABB<2> box, Iyathuum::Color color);
    void setClippingRectangle(Iyathuum::glmAABB<2> box);
    void disableClipping();

  private:
    struct RenderVars;

    void makeShader();

    bool                 _inRenderProcess = false;
    bool                 _clipping        = false;
    Iyathuum::glmAABB<2> _clippingBox;
    std::shared_ptr<RenderVars>           _vars;
  };
}
