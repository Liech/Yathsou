#include "BoxVisualization.h"

#include "YolonaOss/OpenGL/DrawSpecification.h"
#include "YolonaOss/Renderer/BoxRenderer.h"
#include "SuthanusPhysicsLib/Box.h"


namespace Athanah {
  BoxVisualization::BoxVisualization(std::shared_ptr<Suthanus::Box> target, Iyathuum::Color color) {
    _target = target;
    _color  = color ;
  }

  void BoxVisualization::load(YolonaOss::GL::DrawSpecification*)
  {

  }

  void BoxVisualization::draw()
  {
    YolonaOss::BoxRenderer::start();
    glm::mat4 transform = _target->getTransformation();
    transform = glm::scale      (transform, _target->getSize());
    transform = glm::translate  (transform, glm::vec3(-0.5, -0.5, -0.5));
    YolonaOss::BoxRenderer::draw(transform, _color);
    YolonaOss::BoxRenderer::end();
  }
}