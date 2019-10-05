#include "Texture2Tree.h"
#include "../OpenGL/DrawSpecification.h"
#include "../Util/ImageIO.h"
#include "../structs/NMTree.h"
#include "../Renderer/BoxRenderer.h"
#include <iostream>

namespace YolonaOss {
  void YolonaOss::Texture2Tree::load(GL::DrawSpecification*)
  {
    auto map = ImageIO::readImage("YolonaOssData/textures/TinyMap.png");
    _map   = map->map<bool>([](Color const& c) 
      { return (bool)(c.getRed() < 125); });
    _tree  = std::make_shared<NMTree<bool, 2, 2, YolonaOss::TreeMergeBehavior::Max, false> >(_map.get());
    _index = std::make_shared<NMTreeNeighbourIndex<bool, 2, 2, YolonaOss::TreeMergeBehavior::Max, false>>(_tree.get());
    _index->init();
  }

  void YolonaOss::Texture2Tree::draw()
  {
    BoxRenderer::start();
    srand(10);
    auto leafs = _tree->getLeafs();
    float scaling = 0.2f;
    for (auto leaf : leafs)
    {
      float clr = (rand() % 255) / 255.0f;
      glm::vec4 col = glm::vec4(0.5f + clr / 2.0f, 0.5f + clr / 2.0f, 0.5f + clr / 2.0f, 1);
      if (!leaf.value) {
        col = glm::vec4(0.5f, 0.5f + clr / 2.0f, 0.5f + clr / 2.0f, 1);
      }
      glm::vec3 size = glm::vec3(leaf.size* scaling, 0.1f, leaf.size * scaling);
      glm::vec3 pos = glm::vec3(leaf.position[0] * scaling, 0, leaf.position[1] * scaling);
      BoxRenderer::drawBox(pos, size, col);

      for (int dim = 0; dim < 2; dim++) {
        for (auto dir : { NMTreeDirection::Positive/*,NMTreeDirection::Negative*/ })
          for (auto neighb : _index->getNeighbours(leaf.link, dim, dir)) {
            glm::vec3 start = glm::vec3(neighb->getPosition()[0] + neighb->getSize() / 2.0f, 1, neighb->getPosition()[1] + neighb->getSize() / 2.0f);
            glm::vec3 end = glm::vec3(leaf.position[0] + leaf.size / 2.0f, 1, leaf.position[1] + leaf.size / 2.0f);

            BoxRenderer::drawLine(start * scaling, end * scaling, 0.01f, glm::vec4(1, 0, 0, 1));
          }
      }
      
    }
    BoxRenderer::end();
  }
}