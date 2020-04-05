#include "Texture2Tree.h"
#include "../OpenGL/DrawSpecification.h"
#include "../Util/ImageIO.h"
#include "../structs/NMTree.h"
#include "../Renderer/BoxRenderer.h"
#include <iostream>
#include <limits>
#include "../structs/Database.h"
#include "../Util/Geometry.h"
#include "Navigation/MapGroup.h"
#include "Util/Util.h"
#include "Renderer/TextureRenderer.h"
#include "Util/ImageUtil.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext/scalar_constants.hpp>
#include "../Navigation/LinearDiscomfort.h"
#include "../Drawables/Widgets/Slider.h"

float scaling = 1;
namespace YolonaOss {
  
  Texture2Tree::Texture2Tree() {
    std::shared_ptr<Widgets::Slider> b = std::make_shared<Widgets::Slider>("Slider", BoundingBox2(glm::vec2(0, 50), glm::vec2(200, 50)), 0, 1, 0.1f, [this](double val) {
      for (auto u : _unit) {
        u->setSpeed(val);
      }
      
      
      });
    //Database<std::shared_ptr<Widget>>::add(b, { "MouseClick" });
    _drawableList.addDrawable(b);

  }

  void YolonaOss::Texture2Tree::load(GL::DrawSpecification* spec) {
    _landscape = std::make_unique<Landscape<2>>("YolonaOssData/textures/TinyMap.png");

    for (size_t i = 0; i < 4; i++) {
      _unit.push_back(std::make_shared<Unit     <2>>(glm::vec2(4+ i,4  )));
      _unit[i]->_discomfortArea = std::dynamic_pointer_cast<DiscomfortArea<2>>( std::make_shared<LinearDiscomfort<2>>(20, _landscape->_disMapScale));
      _landscape->_dynamicDiscomfort->addDiscomfortArea(_unit[i]->_discomfortArea);
    }

    _spec = spec;
    _mouseClick = [this](double x, double y) {mouseClick(x, y); };
    Database < std::function<void(double, double)>*>::add(&_mouseClick , { "MouseClick" });
  }

  void YolonaOss::Texture2Tree::renderDiscomfort() {
    //auto grayscale = ImageUtil::toGrayscale<double, 2>(&_landscape->_dynamicDiscomfort->_discomfortField, 0, 1);
    ////grayscale->apply([](size_t t, Color& v) {v = Color(v.r(), v.g(), v.b(),v.b() / 8); });
    //TextureRenderer::start();
    //glm::mat4 world(1.0);
    //world = glm::rotate(world, -glm::pi<float>() / 2.0f, glm::vec3(1, 0, 0)); // where x, y, z is axis of rotation (e.g. 0 1 0)
    //world = glm::translate(world, -glm::vec3(0, _landscape->_landscape->getDimension(1), -0.3));
    //world = glm::scale(world, glm::vec3(_landscape->_landscape->getDimension(0), _landscape->_landscape->getDimension(1), 1));

    //TextureRenderer::drawTexture(grayscale.get(), world,glm::vec4(1,0,0,0.5));
    //TextureRenderer::end();
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
      
      auto m = _landscape->getMap(target);
      for(size_t i= 0;i < _unit.size();i++)
        _unit[i]->setTarget(target, m);
    }
  }

  void YolonaOss::Texture2Tree::draw()
  {
    for (size_t i = 0; i < _unit.size(); i++) {
      _unit[i]->_navigationAgent->updatePosition();
      _unit[i]->_discomfortArea->setPosition(_unit[i]->_navigationAgent->getPosition());
    }
    _landscape->_dynamicDiscomfort->updateDiscomfort();
    BoxRenderer::start();
    auto leafs = _landscape->_tree->getLeafs();
    
    for (auto leaf : leafs)
    {
      float clr = 0.3f;
      glm::vec4 col = glm::vec4(clr,clr,clr, 1)*0.1f + glm::vec4(0.9,0.9,0.9,1);
      col[3] = 1;
      if (!leaf.value) {
        col = glm::vec4(0,0,0, 1);
      }
      double distance = 0.5;
      
      if (isinf(distance))
        col = col;
      else if (distance < 0.3)
        col = glm::vec4(1,0,0,1);
      else
        col = glm::vec4(col[0]/distance,col[1] / distance,col[2] / distance , 1);
      glm::vec3 size = glm::vec3(leaf.size* scaling, 0.1f, leaf.size * scaling);
      glm::vec3 pos = glm::vec3(leaf.position[0] * scaling, 0, leaf.position[1] * scaling);
      BoxRenderer::drawBox(pos, size, col);     
    }

    BoxRenderer::drawDot(metaPos, glm::vec3(0.1f), glm::vec4(1, 0, 1, 1));

    for (size_t i = 0; i < _unit.size(); i++)
      BoxRenderer::drawDot(glm::vec3(_unit[i]->getPosition().x,0.1f, _unit[i]->getPosition().y), glm::vec3(0.6f), glm::vec4(1, 0, 0, 1));
    BoxRenderer::end();
    renderDiscomfort();
    _drawableList.draw();
  }
}