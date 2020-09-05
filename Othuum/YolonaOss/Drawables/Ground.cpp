#include "Ground.h"

#include "Renderer/BoxRenderer.h"

namespace YolonaOss
{
  Ground::Ground()
  {

  }

  Ground::~Ground()
  {

  }

  void Ground::load(GL::DrawSpecification*)
  {

  }

  void Ground::draw()
  {
    BoxRenderer::start();

    int amount = 20;
    for (int x = -amount; x < amount; x++)
      for (int y = -amount; y < amount; y++)
      {
        BoxRenderer::drawDot(glm::vec3(x, 0, y), glm::vec3(0.3f, 1, 0.3f), glm::vec4(0.5f, 0.5f, 0.5f,1));
      }
    BoxRenderer::end();
  }
}