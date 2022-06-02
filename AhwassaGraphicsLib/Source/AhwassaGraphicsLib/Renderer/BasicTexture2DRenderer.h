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
  class Uniform;

  class BasicTexture2DRenderer {
  public:
    BasicTexture2DRenderer(Window*);
    BasicTexture2DRenderer(Window*, const std::string& vs, const std::string& fs, std::vector<std::shared_ptr<Ahwassa::Uniform>>);
    virtual ~BasicTexture2DRenderer() {}
    void start();
    void end();
    void draw(const Texture& texture, const glm::vec2& pos, const glm::vec2& size);
    void draw(const Texture& texture, const Iyathuum::glmAABB<2>& box, bool yswap = false);
    void setClippingRectangle(const Iyathuum::glmAABB<2>& box);
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
