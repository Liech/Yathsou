#pragma once

#include <memory>
#include <vector>

#include "IyathuumCoreLib/BaseTypes/glmAABB.h"
#include "IyathuumCoreLib/BaseTypes/Color.h"
#include "AhwassaGraphicsLib/Drawables/Drawable.h"

namespace Ahwassa {
  class Rectangle;

  class Rectangles : Drawable{
  public:
    Rectangles(Window*);

    std::shared_ptr<Rectangle> newRectangle(Iyathuum::glmAABB<2> = Iyathuum::glmAABB<2>(glm::vec2(0,0),glm::vec2(100,100)), Iyathuum::Color = Iyathuum::Color(255,255,255));

    void draw();
  private:
    void shaderCall(std::shared_ptr<Rectangle>);
    void makeShader();

    struct RenderVars;
    std::shared_ptr<RenderVars> _vars;

    std::vector<std::weak_ptr<Rectangle>> _rectangles;
  };
}