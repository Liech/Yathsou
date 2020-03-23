#include "Texture2Tree.h"
#include "../OpenGL/DrawSpecification.h"
#include "../Util/ImageIO.h"
#include "../structs/NMTree.h"
#include "../Renderer/BoxRenderer.h"
#include <iostream>
#include <limits>
#include "../structs/Database.h"
#include "../Util/Geometry.h"
#include "Navigation/DijkstraMap.h"
#include "Navigation/DiscomfortGridMap.h"
#include "Util/Util.h"
#include "Renderer/TextureRenderer.h"
#include "Util/ImageUtil.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext/scalar_constants.hpp>

float scaling = 1;
namespace YolonaOss {

  Texture2Tree::Texture2Tree() :_agent(glm::vec2(3, 3)) {
    _agentMap = std::make_shared<DijkstraMap<2>>();
    _agent.setMap(_agentMap);
  }

  void YolonaOss::Texture2Tree::load(GL::DrawSpecification* spec)
  {
    auto map = ImageIO::readImage("YolonaOssData/textures/TinyMap.png");
    _map   = map->map<bool>([](Color const& c)
      { return (bool)(c.getRed() < 125); });
    _tree  = std::make_shared<NMTree<bool, 2, 2, YolonaOss::TreeMergeBehavior::Max, false> >(_map.get());
    _index = std::make_shared<NMTreeNeighbourIndex<bool, 2, 2, YolonaOss::TreeMergeBehavior::Max, false>>(_tree.get());
    _index->init();
    makeDiscomfort();


    _path = std::dynamic_pointer_cast<DijkstraI<2>>(std::make_shared< NMTreeDijkstra<2> >(glm::vec2(12,12), _tree.get(), _index, [](Tree * node) {return 1; }));

    _spec = spec;
    _mouseClick = [this](double x, double y) {mouseClick(x, y); };
    Database < std::function<void(double, double)>*>::add(&_mouseClick , { "MouseClick" });
  } 

  void YolonaOss::Texture2Tree::makeDiscomfort() {
    std::array<size_t, 2> dim;
    dim[0] = _map->getDimension(0) * 4;
    dim[1] = _map->getDimension(1) * 4;
    double maxDistance = glm::distance(glm::vec2(0, 0), glm::vec2(dim[0] / 2, dim[1] / 2));
    _discomfortMap = std::make_shared<MultiDimensionalArray<double, 2>>(dim);
    _discomfortMap->apply([dim,maxDistance](std::array<size_t, 2> pos, double& val) {
      double distance = glm::distance(glm::vec2(pos[0], pos[1]), glm::vec2(dim[0] / 2, dim[1] / 2));
      val = 1.0 - distance / maxDistance;
    });
    
  }

  void YolonaOss::Texture2Tree::renderDiscomfort() {
    auto grayscale = ImageUtil::toGrayscale<double, 2>(_discomfortMap.get(), 0, 1);
    //grayscale->apply([](size_t t, Color& v) {v = Color(v.r(), v.g(), v.b(),v.b() / 8); });
    TextureRenderer::start();
    glm::mat4 world(1.0);
    world = glm::rotate(world, -glm::pi<float>() / 2.0f, glm::vec3(1, 0, 0)); // where x, y, z is axis of rotation (e.g. 0 1 0)
    world = glm::translate(world, -glm::vec3(0, _map->getDimension(1), -0.3));
    world = glm::scale(world, glm::vec3(_map->getDimension(0), _map->getDimension(1), 1));

    TextureRenderer::drawTexture(grayscale.get(), world,glm::vec4(1,0,1,0.4));
    TextureRenderer::end();
  }

  void YolonaOss::Texture2Tree::mouseClick(double x, double y) {
    glm::vec3 camPos = _spec->getCam()->getPosition();
    glm::vec3 pickDir = _spec->getCam()->getPickRay(x, y);
    Intersection sect = Geometry::intersectRayPlane(camPos, pickDir, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    if (sect.doesIntersect) {
      metaPos = sect.location;
      if (sect.location.x < 0 || sect.location.z < 0 || sect.location.x >= _tree->getSize() || sect.location.z >= _tree->getSize())
        return;
      auto target = glm::vec2(sect.location[0], sect.location[2]);
      _path = std::dynamic_pointer_cast<DijkstraI<2>>(std::make_shared< NMTreeDijkstra<2> >(target, _tree.get(),_index, [](Tree* node) {return 1; }));
      
      _agentMap->setDijkstra(_path);
      _agentMap->setTarget(target);
      _agent.setTarget(target);

    }
  }

  void YolonaOss::Texture2Tree::draw()
  {
    if (!_path) return;
    _agent.updatePosition();
    BoxRenderer::start();
    srand(10);
    auto leafs = _tree->getLeafs();
    
    auto DjPath = (std::dynamic_pointer_cast<NMTreeDijkstra<2>>(_path))->getPath(_agent.getPosition());
    std::set<Tree*> DjPathSet(DjPath.begin(), DjPath.end());

    //if (false)
    for (auto leaf : leafs)
    {

      float clr = 0.3f;// (rand() % 255) / 255.0f;
      glm::vec4 col = glm::vec4(clr,clr,clr, 1)*0.1f + glm::vec4(0.9,0.9,0.9,1);
      col[3] = 1;
      if (!leaf.value) {
        col = glm::vec4(0,0,0, 1);
      }
      double distance = _path->getDistance(Util<2>::array2Vec(leaf.position) * scaling);
      
      if (isinf(distance))
        col = col;
      else if (DjPathSet.count(leaf.link))
        col = glm::vec4(0, 0, 1,1);
      else if (distance < 0.3)
        col = glm::vec4(1,0,0,1);
      else
        col = glm::vec4(col[0]/distance,col[1] / distance,col[2] / distance , 1);
      glm::vec3 size = glm::vec3(leaf.size* scaling, 0.1f, leaf.size * scaling);
      glm::vec3 pos = glm::vec3(leaf.position[0] * scaling, 0, leaf.position[1] * scaling);
      BoxRenderer::drawBox(pos, size, col);
      //if (!(leaf.position[0] == 1 && leaf.position[1] == 1))
        //continue;
      if (false)
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
    BoxRenderer::drawDot(glm::vec3(_agent.getPosition().x,0.1f,_agent.getPosition().y), glm::vec3(0.1f), glm::vec4(1, 1, 0, 1));
    BoxRenderer::end();
    renderDiscomfort();
  }
}