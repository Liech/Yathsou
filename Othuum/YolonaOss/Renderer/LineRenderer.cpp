#include "LineRenderer.h"
#include "glad/glad.h"
#include "../OpenGL/Camera.h"
#include "../OpenGL/PositionColorVertex.h"

namespace YolonaOss {
  void LineRenderer::load(GL::DrawSpecification* spec)
  {
    _spec = spec;
  }

  void LineRenderer::start()
  {
    
  }

  void LineRenderer::end()
  {
    
  }

  void LineRenderer::drawLine(glm::vec3 start, glm::vec3 end, float thickness, glm::vec4 color)
  {
    glm::vec3 normStart = _spec->getCam()->getPosition() - start;
    glm::vec3 normEnd   = _spec->getCam()->getPosition() - end;
    glm::vec3 crossStart = glm::cross(normStart, start - end);
    glm::vec3 crossEnd = glm::cross(normEnd, end-start);

    normStart /= normStart.length();

    glm::vec3 a = start + normStart;
    glm::vec3 b = start - normStart;
    glm::vec3 c = end + normEnd;
    glm::vec3 d = end - normEnd;

    std::vector<GL::PositionColorVertex> vertices = {
      GL::PositionColorVertex(a,color),
      GL::PositionColorVertex(b,color),
      GL::PositionColorVertex(c,color),
      GL::PositionColorVertex(c,color),
      GL::PositionColorVertex(d,color),
      GL::PositionColorVertex(a,color)
    };
  }

}