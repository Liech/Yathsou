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
  class BoxRenderer;
  class RectangleRenderer;
  class SphereRenderer;
  class BasicTextRenderer;
  class BasicRectangleRenderer;
  class BasicTexture2DRenderer;

  class Window;
  class Camera;
  
  class Renderer {
  public:
    Renderer(Window*, std::shared_ptr<Camera>);
    std::shared_ptr<Dot      > newDot(const glm::vec3& pos, float size                                                       , Iyathuum::Color = Iyathuum::Color(255, 255, 255));
    std::shared_ptr<Line     > newLine(const glm::vec3& start, const glm::vec3& end, float size                              , Iyathuum::Color = Iyathuum::Color(255, 255, 255));
    std::shared_ptr<Box      > newBox(const glm::mat4&                                                                       , Iyathuum::Color = Iyathuum::Color(255, 255, 255));
    std::shared_ptr<Rectangle> newRectangle(Iyathuum::glmAABB<2> = Iyathuum::glmAABB<2>(glm::vec2(0, 0), glm::vec2(100, 100)), Iyathuum::Color = Iyathuum::Color(255, 255, 255));
    std::shared_ptr<Sphere   > newSphere(const glm::vec3& pos, float size                                                    , Iyathuum::Color = Iyathuum::Color(255, 255, 255));

    BasicRectangleRenderer& rectangle();
    BasicTextRenderer     & text();
    BasicTexture2DRenderer& texture();

    void setLightDir(const glm::vec3&);

    void draw();
  private:
    std::shared_ptr<BoxRenderer           > _box      ;
    std::shared_ptr<RectangleRenderer     > _rectangle;
    std::shared_ptr<SphereRenderer        > _sphere   ;

    std::shared_ptr<BasicTextRenderer     > _bText     ;
    std::shared_ptr<BasicRectangleRenderer> _bRectangle;
    std::shared_ptr<BasicTexture2DRenderer> _bTexture  ;

    Window* _window;
  };
}