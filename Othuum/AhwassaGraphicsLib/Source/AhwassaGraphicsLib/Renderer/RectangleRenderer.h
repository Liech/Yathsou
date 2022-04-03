#pragma once

#include <memory>
#include <vector>

#include "IyathuumCoreLib/BaseTypes/glmAABB.h"
#include "IyathuumCoreLib/BaseTypes/Color.h"
#include "AhwassaGraphicsLib/Drawables/Drawable.h"

namespace Ahwassa {
  class Rectangle;

  class RectangleRenderer : Drawable{
  public:
    RectangleRenderer(Window*);

    std::shared_ptr<Rectangle> newRectangle(Iyathuum::glmAABB<2> = Iyathuum::glmAABB<2>(glm::vec2(0,0),glm::vec2(100,100)), Iyathuum::Color = Iyathuum::Color(255,255,255));

    void draw();
  private:
    void shaderCall(const std::vector<glm::mat4>&, const std::vector<glm::vec3>&, size_t amount);
    void makeShader();
    void makeModelArray(size_t bufferSize);

    struct RenderVars;
    std::shared_ptr<RenderVars> _vars;
    size_t _bufferSize = 1000;

    std::vector<std::weak_ptr<Rectangle>> _RectangleRenderer;
  };
}