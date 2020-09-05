#include "Protagonist.h"

#include "YolonaOss/Renderer/BoxRenderer.h"

namespace Fatboy
{
  Protagonist::Protagonist()
  {

  }
  void Protagonist::load(YolonaOss::GL::DrawSpecification*)
  {

  }

  void Protagonist::draw()
  {
    YolonaOss::BoxRenderer::start();
    YolonaOss::BoxRenderer::drawDot(getPosition(), glm::vec3(1, 1, 1), glm::vec4(1,0,0,1));
    YolonaOss::BoxRenderer::end();
  }

  void Protagonist::update()
  {

  }

  glm::vec3 Protagonist::getPosition()
  {
    return _pos;
  }

}