#pragma once

#include <memory>

#include "IyathuumCoreLib/BaseTypes/glmAABB.h"
#include "IyathuumCoreLib/BaseTypes/Color.h"

namespace Ahwassa {
  class Box;
  class Dot;
  class Line;
  class Rectangle;
  class Sphere;
  class RectangleRenderer;
  class SphereRenderer;
  class DirectTextRenderer;
  class DirectRectangleRenderer;
  class DirectTexture2DRenderer;

  class Window;
  class Camera;
  
  enum class GlobalRenderMode {
    Direct, Deferred
  };

  class Renderer {
  public:
    Renderer(Window*, std::shared_ptr<Camera>);
    std::shared_ptr<Rectangle> newRectangle(const Iyathuum::glmAABB<2>& = Iyathuum::glmAABB<2>(glm::vec2(0, 0), glm::vec2(100, 100)), Iyathuum::Color = Iyathuum::Color(255, 255, 255));

    DirectRectangleRenderer& rectangle();
    DirectTextRenderer     & text()     ;
    DirectTexture2DRenderer& texture()  ;

    GlobalRenderMode renderMode() const;
    void             setRenderMode(GlobalRenderMode);

    void setLightDir(const glm::vec3&);

    void draw();
  private:
    std::shared_ptr<RectangleRenderer     > _rectangle;
    std::shared_ptr<SphereRenderer        > _sphere   ;

    std::shared_ptr<DirectTextRenderer     > _bText     ;
    std::shared_ptr<DirectRectangleRenderer> _bRectangle;
    std::shared_ptr<DirectTexture2DRenderer> _bTexture  ;

    GlobalRenderMode                        _renderMode = GlobalRenderMode::Direct;
    Window* _window;
  };
}