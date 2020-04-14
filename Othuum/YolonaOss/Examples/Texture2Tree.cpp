#include "Texture2Tree.h"
#include "../OpenGL/DrawSpecification.h"
#include "../Util/ImageIO.h"
#include "../Renderer/BoxRenderer.h"
#include <iostream>
#include <limits>
#include "IyathuumCoreLib/Singleton/Database.h"
#include "IyathuumCoreLib/Tree/NMTree.h"
#include "IyathuumCoreLib/Util/ImageUtil.h"
#include "../Util/Geometry.h"
#include "Navigation/MapGroup.h"
#include "Util/Util.h"
#include "Renderer/TextureRenderer.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext/scalar_constants.hpp>
#include "../Drawables/Widgets/Slider.h"
#include "../Drawables/Widgets/ListLayout.h"
#include "../Drawables/Widgets/Label.h"
#include "../Renderer/ArrowRenderer.h"

#include <functional>

float scaling = 1;
namespace YolonaOss {
  
  Texture2Tree::Texture2Tree() {


  }

  void YolonaOss::Texture2Tree::load(GL::DrawSpecification* spec) {
    _landscape = std::make_unique<Landscape<2>>("YolonaOssData/textures/TinyMap.png");

    int amount = 20;
    float distance = 1.0f;
    for(size_t x = 0; x < amount; x++){
      for (size_t i = 0; i < amount; i++) {
        auto u = std::make_shared<Unit     <2>>(glm::vec2(4 + i * distance, 4 + x* distance), glm::vec2(0, 0.1f));
        _unit.push_back(u);
        _landscape->_unitAgents->addAgent(_unit[_unit.size()-1]->_navigationAgent);
      }
    }

    _spec = spec;
    _mouseClick = [this](double x, double y) {mouseClick(x, y); return true; };
    Iyathuum::Database < std::function<bool(double, double)>*>::add(&_mouseClick , { "MouseClick" });


    _layout = std::make_shared<Widgets::ListLayout>(Iyathuum::AABB<2>({ 0.0, 50.0 }, { 350.0, (double)(spec->height - 50)}));
    _drawableList.addDrawable(_layout);

    for (size_t i = 0; i < 20; i++)
      _config[i] = 0;

    addSlider("land"  , 0, 0, 1);
    addSlider("navi"  , 1, 0, 1);
    addSlider("direct", 2, 0, 1);
    addSlider("shy"   , 3, 0, 1);
    addSlider("cuddle", 4, 0, 1);
    addSlider("align" , 5, 0, 1);
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
    glm::vec3 pickDir = _spec->getCam()->getPickRay((float)x, (float)y);
    Intersection sect = Geometry::intersectRayPlane(camPos, pickDir, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    if (sect.doesIntersect) {
      metaPos = sect.location;
      if (sect.location.x < 0 || sect.location.z < 0 || sect.location.x >= _landscape->_tree->getSize() || sect.location.z >= _landscape->_tree->getSize())
        return;
      auto target = glm::vec2(sect.location[0], sect.location[2]);
      
      auto m = _landscape->getMap(target);
      for (size_t i = 0; i < _unit.size(); i++) {
        _unit[i]->setTarget(target, m);
      }
    }
  }

  void YolonaOss::Texture2Tree::draw()
  {
    #pragma omp parallel for
    for (int64_t i = 0; i < (int64_t)_unit.size(); i++) {
      _unit[i]->_navigationAgent->updatePosition();
    }

    _landscape->_unitAgents->updateAgents();
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
    BoxRenderer::end();
    //BoxRenderer::start();
    //for (size_t i = 0; i < _unit.size(); i++) {
    //  BoxRenderer::drawDot(glm::vec3(_unit[i]->getPosition().x, 0.5f, _unit[i]->getPosition().y), glm::vec3(1)*0.1f,glm::vec4(1, 0, 0, 1));
    //}
    //BoxRenderer::end();
    ArrowRenderer::start();
    for (size_t i = 0; i < _unit.size(); i++) {
      glm::vec3 ori = glm::vec3(_unit[i]->getOrientation()[0], 0   , _unit[i]->getOrientation()[1]);
      glm::vec3 pos = glm::vec3(_unit[i]->getPosition().x    , 0.5f, _unit[i]->getPosition().y    );
      glm::vec4 c = glm::vec4(1, 0, 0, 1);
      if (_landscape->arrival && _landscape->arrival->isArrived(_unit[i]->_navigationAgent.get()))
        c = glm::vec4(0, 1, 0, 1);
      ArrowRenderer::drawArrow(pos-ori*0.5f, ori, 0.5f, c);
    }
    ArrowRenderer::end();
    renderDiscomfort();
    _drawableList.draw();
  }

  void Texture2Tree::addSlider(std::string text, int id, double min, double max) {
    auto v = [this, id](double val) { 
      for (auto u : _unit) {
        if (u->_navigationAgent->getMap())
          std::dynamic_pointer_cast<MapGroup<2>>(u->_navigationAgent->getMap())->setWeight(id, (float)val);
      }
      _config[id] = (float)val;
      _landscape->setConfig(_config);
    };

    std::shared_ptr<Widgets::Slider> a = std::make_shared<Widgets::Slider>(Iyathuum::AABB<2>({ 0, 50 }, { 200, 50 }), min, max, _config[id], v);
    std::shared_ptr<Widgets::Label>  b = std::make_shared<Widgets::Label>(text, Iyathuum::AABB<2>({ 0, 50 }, { 150, 50 }));
    auto layout = std::make_shared<Widgets::ListLayout>(Iyathuum::AABB<2>({ 0, 50 }, { 350, 50 }));
    layout->setHorizontal(true);
    layout->addWidget(b);
    layout->addWidget(a);
    _layout->addWidget(layout);
  }
}