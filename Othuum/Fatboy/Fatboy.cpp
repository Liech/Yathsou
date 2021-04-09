#include "Fatboy.h"

#include "SuthanusPhysicsLib/PhysicEngine.h"
#include "SuthanusPhysicsLib/Box.h"
#include "AhwassaGraphicsLib/Drawables/FPS.h"
#include "AhwassaGraphicsLib/Drawables/Background.h"
#include "AhwassaGraphicsLib/Core/Camera.h"
#include "Protagonist.h"
#include "GameConfiguration.h"
#include "HaasScriptingLib/ScriptEngine.h"

#include <IyathuumCoreLib/lib/glm/gtc/matrix_transform.hpp>
#include "AhwassaGraphicsLib/BasicRenderer/BasicBoxRenderer.h"
#include "AezeselFileIOLib/ImageIO.h"
#include <iostream>

namespace Fatboy
{
  Fatboy::Fatboy(Ahwassa::Window* w)
  {
    _preDrawables.push_back(std::make_shared<Ahwassa::Background>());
    _postDrawables.push_back(std::make_shared<Ahwassa::FPS>());
    //_preDrawables->addDrawable(std::make_shared<YolonaOss::Ground>());
    _context = std::make_shared<Context>();

    initPhysic();
    _protagonist = std::make_shared<Protagonist>(_context,&_drawDebug, w);
    //initEnemys();
    _context->physic()->setDebugDrawer(new BulletDebugDrawer());

    loadLandscapeModel();
  }

  void Fatboy::initPhysic()
  {
    _context->physic()->setTicksPerSecond(GameConfiguration::instance().TicksPerSecond);
    _landscape = _context->physic()->newBox(glm::vec3(0, 0, 0), glm::vec3(20, 0, 20), false);
    _physicAPI = std::make_shared<ScriptAPI>(_context->physic().get());
    _physicAPI->registerAPI(_context->script().get());
    _land = _context->physic()->newHeightMap(glm::vec3(0, 2, 0));
  }

  void Fatboy::initEnemys()
  {
    auto tank = std::make_shared<Unit>(_context,getWindow());
    tank->setStartPosition(glm::vec3(-3, 2, -3));
    _context->units()->addUnit(tank);

    tank = std::make_shared<Unit>(_context,getWindow());
    tank->setStartPosition(glm::vec3(3, 2, -3));
    _context->units()->addUnit(tank);

    tank = std::make_shared<Unit>(_context, getWindow());
    tank->setStartPosition(glm::vec3(3, 2, 3));
    _context->units()->addUnit(tank);

    tank = std::make_shared<Unit>(_context,getWindow());
    tank->setStartPosition(glm::vec3(-3, 2, 3));
    _context->units()->addUnit(tank);
  }

  void Fatboy::update()
  {
    _protagonist->update();
    _context->physic()->update();
  }

  void Fatboy::loadLandscapeModel()
  {
    auto landscapeMesh = _land->getMesh();
  }

  void Fatboy::drawLandscape()
  {
    YolonaOss::BoxRenderer::start();
    glm::mat4 transform = _landscape->getTransformation();
    transform = glm::scale(transform, _landscape->getSize());
    transform = glm::translate(transform, glm::vec3(-0.5, -0.5, -0.5));
    YolonaOss::BoxRenderer::draw(transform, glm::vec4(0, 0, 1, 1));
    YolonaOss::BoxRenderer::end();
  }

  void Fatboy::draw()
  {
    _preDrawables->draw();

    if (!_drawDebug)
      drawLandscape();
    _context->bullets()->draw();
    _context->units  ()->draw();
    _postDrawables->draw();
    if (_drawDebug)
    {
      YolonaOss::BoxRenderer::start();
      _context->physic()->debugDrawWorld();
      YolonaOss::BoxRenderer::end();
    }
  }
}