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
#include "Navigation/GradientGridMap.h"
#include "Navigation/MapGroup.h"
#include "Util/Util.h"
#include "Renderer/TextureRenderer.h"
#include "Util/ImageUtil.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext/scalar_constants.hpp>

float scaling = 1;
namespace YolonaOss {
  
  Texture2Tree::Texture2Tree() {
  }

  void YolonaOss::Texture2Tree::load(GL::DrawSpecification* spec)
  {
    _landscape = std::make_unique<Landscape<2>>("YolonaOssData/textures/TinyMap.png");
    _unit = std::make_unique<Unit     <2>>(_landscape.get());

    _spec = spec;
    _mouseClick = [this](double x, double y) {mouseClick(x, y); };
    Database < std::function<void(double, double)>*>::add(&_mouseClick , { "MouseClick" });
  }

  void YolonaOss::Texture2Tree::renderDiscomfort() {
    auto grayscale = ImageUtil::toGrayscale<double, 2>(_landscape->_staticDiscomfort.get(), 0, 1);
    //grayscale->apply([](size_t t, Color& v) {v = Color(v.r(), v.g(), v.b(),v.b() / 8); });
    TextureRenderer::start();
    glm::mat4 world(1.0);
    world = glm::rotate(world, -glm::pi<float>() / 2.0f, glm::vec3(1, 0, 0)); // where x, y, z is axis of rotation (e.g. 0 1 0)
    world = glm::translate(world, -glm::vec3(0, _landscape->_landscape->getDimension(1), -0.3));
    world = glm::scale(world, glm::vec3(_landscape->_landscape->getDimension(0), _landscape->_landscape->getDimension(1), 1));

    TextureRenderer::drawTexture(grayscale.get(), world,glm::vec4(1,1,1,0.11));
    TextureRenderer::end();
  }

  void YolonaOss::Texture2Tree::mouseClick(double x, double y) {
    glm::vec3 camPos = _spec->getCam()->getPosition();
    glm::vec3 pickDir = _spec->getCam()->getPickRay(x, y);
    Intersection sect = Geometry::intersectRayPlane(camPos, pickDir, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    if (sect.doesIntersect) {
      metaPos = sect.location;
      if (sect.location.x < 0 || sect.location.z < 0 || sect.location.x >= _landscape->_tree->getSize() || sect.location.z >= _landscape->_tree->getSize())
        return;
      auto target = glm::vec2(sect.location[0], sect.location[2]);
      
      _unit->setTarget(target);
    }
  }

  void YolonaOss::Texture2Tree::draw()
  {
    _unit->_navigationAgent->updatePosition();
    BoxRenderer::start();
    srand(10);
    auto leafs = _landscape->_tree->getLeafs();
    
    //auto DjPath = (std::dynamic_pointer_cast<NMTreeDijkstra<2>>(_landscape->_path))->getPath(_unit->_navigationAgent->getPosition());
    //std::set<Tree*> DjPathSet(DjPath.begin(), DjPath.end());

    //if (false)
    for (auto leaf : leafs)
    {

      float clr = 0.3f;// (rand() % 255) / 255.0f;
      glm::vec4 col = glm::vec4(clr,clr,clr, 1)*0.1f + glm::vec4(0.9,0.9,0.9,1);
      col[3] = 1;
      if (!leaf.value) {
        col = glm::vec4(0,0,0, 1);
      }
      double distance = 0.5;// _landscape->_path->getDistance(Util<2>::array2Vec(leaf.position) * scaling);
      
      if (isinf(distance))
        col = col;
      //else if (DjPathSet.count(leaf.link))
      //  col = glm::vec4(0, 0, 1,1);
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
          for (auto neighb : _landscape->_index->getNeighbours(leaf.link, dim, dir)) {
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
    BoxRenderer::drawDot(glm::vec3(_unit->_navigationAgent->getPosition().x,0.1f, _unit->_navigationAgent->getPosition().y), glm::vec3(0.6f), glm::vec4(1, 0, 0, 1));
    BoxRenderer::end();
    //renderDiscomfort();
  }
}