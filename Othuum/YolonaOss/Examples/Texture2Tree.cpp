#include "Texture2Tree.h"
#include "../OpenGL/DrawSpecification.h"
#include "../Util/ImageIO.h"
#include "../structs/NMTree.h"
#include "../Renderer/BoxRenderer.h"
#include <iostream>
#include <limits>
#include "../structs/Database.h"
#include "../Util/Geometry.h"

float scaling = 0.2f;
namespace YolonaOss {
  void YolonaOss::Texture2Tree::load(GL::DrawSpecification* spec)
  {
    auto map = ImageIO::readImage("YolonaOssData/textures/TinyMap.png");
    _map   = map->map<bool>([](Color const& c) 
      { return (bool)(c.getRed() < 125); });
    _tree  = std::make_shared<NMTree<bool, 2, 2, YolonaOss::TreeMergeBehavior::Max, false> >(_map.get());
    _index = std::make_shared<NMTreeNeighbourIndex<bool, 2, 2, YolonaOss::TreeMergeBehavior::Max, false>>(_tree.get());
    _index->init();

    _path = std::make_shared< Dijkstra<Tree> >(
        _tree->getLeaf({ 12,12 }),
        [](Tree* a, Tree* b) { 
        bool A = a->getContent();
        bool B = b->getContent();
        if (!A || !B)
          return std::numeric_limits<double>::infinity();
        else 
          return 1.0;
      },
        [this](Tree* n) { return _index->getAllNeighbours(n); }
    );

    _spec = spec;
    _mouseClick = [this](double x, double y) {mouseClick(x, y); };
    Database < std::function<void(double, double)>*>::add(&_mouseClick , { "MouseClick" });

  }

  void YolonaOss::Texture2Tree::mouseClick(double x, double y) {
    glm::vec3 camPos = _spec->getCam()->getPosition();
    glm::vec3 pickDir = _spec->getCam()->getPickRay(x, y);
    Intersection sect = Geometry::intersectRayPlane(camPos, pickDir, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    if (sect.doesIntersect) {
      metaPos = sect.location;
      if (sect.location.x < 0 || sect.location.y < 0 || sect.location.x > _tree->getSize() || sect.location.y > _tree->getSize())
        return;
      _path = std::make_shared< Dijkstra<Tree> >(
        _tree->getLeaf({ (size_t)(sect.location[0] / scaling),(size_t)(sect.location[2] / scaling)}),
        [](Tree* a, Tree* b) {
          bool A = a->getContent();
          bool B = b->getContent();
          if (!A || !B)
            return std::numeric_limits<double>::infinity();
          else
            return 1.0;
        },
        [this](Tree* n) { return _index->getAllNeighbours(n); }
        );

    }
  }

  void YolonaOss::Texture2Tree::draw()
  {
    BoxRenderer::start();
    srand(10);
    auto leafs = _tree->getLeafs();
    for (auto leaf : leafs)
    {
      //Tree::Leaf leaf;
      //leaf.link = _tree->getLeaf({ 12,12 });
      //leaf.position = leaf.link->getPosition();
      //leaf.size = leaf.link->getSize();
      //leaf.value = leaf.link->getContent();

      float clr = 0.3f;// (rand() % 255) / 255.0f;
      glm::vec4 col = glm::vec4(clr,clr,clr, 1)*0.1f + glm::vec4(0.9,0.9,0.9,1);
      col[3] = 1;
      if (!leaf.value) {
        col = glm::vec4(0,0,0, 1);
      }
      double distance = _path->getGradient(leaf.link) / (_path->getMaxValue()  / 4.0);
      if (isinf(distance))
        col = col;
      else if (distance == 0)
        col = glm::vec4(1,0,0,1);
      else
        col = glm::vec4(col[0]/distance,col[1] / distance,col[2] / distance , 1);
      glm::vec3 size = glm::vec3(leaf.size* scaling, 0.1f, leaf.size * scaling);
      glm::vec3 pos = glm::vec3(leaf.position[0] * scaling, 0, leaf.position[1] * scaling);
      BoxRenderer::drawBox(pos, size, col);
      //if (!(leaf.position[0] == 1 && leaf.position[1] == 1))
        //continue;

      for (int dim = 0; dim < 2; dim++) {
        for (auto dir : { NMTreeDirection::Positive,NMTreeDirection::Negative })
          for (auto neighb : _index->getNeighbours(leaf.link, dim, dir)) {
            glm::vec3 start = glm::vec3(neighb->getPosition()[0] + neighb->getSize() / 2.0f, 0.5f, neighb->getPosition()[1] + neighb->getSize() / 2.0f);
            glm::vec3 end = glm::vec3(leaf.position[0] + leaf.size / 2.0f, 0.5f, leaf.position[1] + leaf.size / 2.0f);
            glm::vec4 c = glm::vec4(1, 0, 0, 1);
            if (dir == NMTreeDirection::Positive) 
              c = glm::vec4(1, 0, 0, 1);
            else
              c = glm::vec4(0, 0, 1, 1);
            glm::vec3 s = glm::vec3(0, 0, 0);
            if (dir == NMTreeDirection::Negative)
              s = glm::vec3(0.01f, 0.01f, 0.01f);
            //c = 
            BoxRenderer::drawLine(start * scaling+s, end * scaling+s, 0.01f, c);
          }
      }
      
    }

    BoxRenderer::drawDot(metaPos, glm::vec3(0.1f), glm::vec4(1, 0, 1, 1));
    BoxRenderer::end();
  }
}