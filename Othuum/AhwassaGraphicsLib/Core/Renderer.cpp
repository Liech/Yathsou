#include "Renderer.h"

#include "Renderer/RectangleRenderer.h"
#include "Renderer/BoxRenderer.h"
#include "Renderer/SphereRenderer.h"

#include "Renderer/Box.h"
#include "Renderer/Dot.h"
#include "Renderer/Line.h"
#include "Renderer/Rectangle.h"
#include "Renderer/Sphere.h"

namespace Ahwassa {
  Renderer::Renderer(Window* window, std::shared_ptr<Camera> cam) {
    _window = window;
    
    _box       = std::make_shared<BoxRenderer      >(cam   );
    _rectangle = std::make_shared<RectangleRenderer>(window);
    _sphere    = std::make_shared<SphereRenderer   >(cam   );
  }

  std::shared_ptr<Dot> Renderer::newDot(const glm::vec3& pos, float size, Iyathuum::Color clr) {
    return _box->newDot(pos, size, clr);
  }

  std::shared_ptr<Line> Renderer::newLine(const glm::vec3& start, const glm::vec3& end, float size, Iyathuum::Color clr) {
    return _box->newLine(start,end,size,clr);
  }

  std::shared_ptr<Box> Renderer::newBox(const glm::mat4& mat, Iyathuum::Color clr) {
    return _box->newBox(mat, clr);
  }

  std::shared_ptr<Rectangle> Renderer::newRectangle(Iyathuum::glmAABB<2> loc, Iyathuum::Color clr) {
    return _rectangle->newRectangle(loc, clr);
  }

  std::shared_ptr<Sphere> Renderer::newSphere(const glm::vec3& pos, float size, Iyathuum::Color clr) {
    return _sphere->newSphere(pos, size, clr);
  }

  void Renderer::setLightDir(const glm::vec3& dir) {
    _sphere   ->setLightDir(dir);
    _box      ->setLightDir(dir);
  }

  void Renderer::draw() {
    _sphere->draw();
    _box   ->draw();
    _sphere->draw();
  }
}