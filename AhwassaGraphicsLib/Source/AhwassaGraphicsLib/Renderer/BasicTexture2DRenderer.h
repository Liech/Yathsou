#pragma once

#include <iostream>
#include "IyathuumCoreLib/Singleton/Factory.h"
#include <glm/glm.hpp>
#include "IyathuumCoreLib/BaseTypes/glmAABB.h"
#include "IyathuumCoreLib/BaseTypes/Color.h"
#include <memory>

#include <map>

namespace Ahwassa {
  class Window;
  class Texture;

  class BasicTexture2DRenderer {
  public:
    BasicTexture2DRenderer(Window*);
    virtual ~BasicTexture2DRenderer() {}
    void start();
    void end();
    void draw(const Texture& texture, glm::vec2 pos, glm::vec2 size);
    void draw(const Texture& texture, Iyathuum::glmAABB<2> box, bool yswap = false);
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
