#include "Renderer.h"


#include "AhwassaGraphicsLib/Renderer/Primitives/Box.h"
#include "AhwassaGraphicsLib/Renderer/Primitives/Dot.h"
#include "AhwassaGraphicsLib/Renderer/Primitives/Line.h"
#include "AhwassaGraphicsLib/Renderer/Primitives/Rectangle.h"
#include "AhwassaGraphicsLib/Renderer/Primitives/Sphere.h"

#include "AhwassaGraphicsLib/Renderer/Private/RectangleRenderer.h"
#include "AhwassaGraphicsLib/Renderer/Private/DirectTextRenderer.h"
#include "AhwassaGraphicsLib/Renderer/Private/DirectRectangleRenderer.h"
#include "AhwassaGraphicsLib/Renderer/Private/DirectTexture2DRenderer.h"

namespace Ahwassa {
  Renderer::Renderer(Window* window, std::shared_ptr<Camera> cam) {
    _window = window;
    
    _rectangle = std::make_shared<RectangleRenderer     >(window);
    _bRectangle= std::make_shared<DirectRectangleRenderer>(window);
    _bText     = std::make_shared<DirectTextRenderer     >(window);
    _bTexture  = std::make_shared<DirectTexture2DRenderer>(window);
  }

  std::shared_ptr<Rectangle> Renderer::newRectangle(const Iyathuum::glmAABB<2>& loc, Iyathuum::Color clr) {
    return _rectangle->newRectangle(loc, clr);
  }


  void Renderer::setLightDir(const glm::vec3& dir) {
  }

  void Renderer::draw() {
  }

  DirectRectangleRenderer& Renderer::rectangle() {
    return *_bRectangle;
  }

  DirectTextRenderer& Renderer::text() {
    return *_bText;
  }

  DirectTexture2DRenderer& Renderer::texture() {
    return *_bTexture;
  }

  GlobalRenderMode Renderer::renderMode() const {
    return _renderMode;
  }

  void Renderer::setRenderMode(GlobalRenderMode mode) {
    _renderMode = mode;
  }
}