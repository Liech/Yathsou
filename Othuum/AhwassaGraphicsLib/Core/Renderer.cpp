#include "Renderer.h"

#include "AhwassaGraphicsLib/Renderer/RectangleRenderer.h"
#include "AhwassaGraphicsLib/Renderer/BoxRenderer.h"
#include "AhwassaGraphicsLib/Renderer/SphereRenderer.h"

#include "AhwassaGraphicsLib/Renderer/Box.h"
#include "AhwassaGraphicsLib/Renderer/Dot.h"
#include "AhwassaGraphicsLib/Renderer/Line.h"
#include "AhwassaGraphicsLib/Renderer/Rectangle.h"
#include "AhwassaGraphicsLib/Renderer/Sphere.h"
#include "AhwassaGraphicsLib/BasicRenderer/BasicTextRenderer.h"
#include "AhwassaGraphicsLib/BasicRenderer/BasicRectangleRenderer.h"
#include "AhwassaGraphicsLib/BasicRenderer/BasicTexture2DRenderer.h"
#include "AhwassaGraphicsLib/Renderer/DiffuseMeshRenderer.h"

namespace Ahwassa {
  Renderer::Renderer(Window* window, std::shared_ptr<Camera> cam) {
    _window = window;
    
    _box       = std::make_shared<BoxRenderer           >(cam   );
    _rectangle = std::make_shared<RectangleRenderer     >(window);
    _sphere    = std::make_shared<SphereRenderer        >(cam   );
    _bRectangle= std::make_shared<BasicRectangleRenderer>(window);
    _bText     = std::make_shared<BasicTextRenderer     >(window);
    _bTexture  = std::make_shared<BasicTexture2DRenderer>(window);
    _bMesh     = std::make_shared<DiffuseMeshRenderer   >(cam   );
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
    _bMesh ->draw();
  }

  BasicRectangleRenderer& Renderer::rectangle() {
    return *_bRectangle;
  }

  BasicTextRenderer& Renderer::text() {
    return *_bText;
  }

  BasicTexture2DRenderer& Renderer::texture() {
    return *_bTexture;
  }

  DiffuseMeshRenderer& Renderer::mesh() {
    return *_bMesh;
  }
}