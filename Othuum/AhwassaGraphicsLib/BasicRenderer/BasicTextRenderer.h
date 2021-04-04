#pragma once

#include <iostream>
#include <memory>
#include <map>

#include "IyathuumCoreLib/lib/glm/glm.hpp"
#include "IyathuumCoreLib/BaseTypes/glmAABB.h"
#include "IyathuumCoreLib/BaseTypes/Color.h"

namespace Ahwassa {
  class Window;

  struct BasicTextRenderer_Character {
    int        TextureID;  // ID handle of the glyph texture
    glm::ivec2 Size;       // Size of glyph
    glm::ivec2 Bearing;    // Offset from baseline to left/top of glyph
    int        Advance;    // Offset to advance to next glyph
  };
  class BasicTextRenderer {
  public:
    BasicTextRenderer(Window*);
    virtual   ~BasicTextRenderer() {}
    void      start();
    void      end();
    void      drawText(std::string text, float x, float y, float scale, Iyathuum::Color color = Iyathuum::Color(0,0,0));
    void      drawText(std::string text, glm::vec2 pos, float scale   , Iyathuum::Color color = Iyathuum::Color(0,0,0));
    glm::vec2 getTextSize(std::string text, float scale);
    void      setClippingRectangle(Iyathuum::glmAABB<2> box);
    void      disableClipping();

  private:

    struct RenderVars;

    void makeShader();
    void makeFreetype();

    bool                 _inRenderProcess = false;
    bool                 _clipping        = false;
    Iyathuum::glmAABB<2> _clippingBox            ;

    std::shared_ptr<RenderVars> _vars;
    int _maxHeight = 0;

  };
}