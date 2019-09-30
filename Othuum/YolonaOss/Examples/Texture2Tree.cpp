#include "Texture2Tree.h"
#include "../OpenGL/DrawSpecification.h"
#include "../Util/ImageIO.h"
#include "../structs/NMTree.h"
#include "../Renderer/BoxRenderer.h"
#include <iostream>

namespace YolonaOss {
  void YolonaOss::Texture2Tree::load(GL::DrawSpecification*)
  {
    auto map = ImageIO::readImage("YolonaOssData/textures/SmallMap.png");
    _map = map->map<bool>([](Color const& c) { return (bool)(c.getRed() > 125); });
    //NMTree<bool, 2, 2,YolonaOss::TreeMergeBehavior::Max,false> t;

  }

  void YolonaOss::Texture2Tree::draw()
  {
    BoxRenderer::start();

    for(int x = 0 ;x < _map->getDimension(0);x++)
      for (int y = 0; y < _map->getDimension(1); y++) {
        bool v = _map->getValue(x, y);
        if (v)
          BoxRenderer::drawDot(glm::vec3(x/5.0f, 0, y/5.0f), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec4(1, 1, 1, 1));
      }

    BoxRenderer::end();
  }
}