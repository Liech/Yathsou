#include "Fatboy.h"

#include "SuthanusPhysicsLib/PhysicEngine.h"
#include "SuthanusPhysicsLib/Box.h"
#include "YolonaOss/Drawables/FPS.h"
#include "YolonaOss/Drawables/Background.h"
#include "YolonaOss/Drawables/Ground.h"
#include "YolonaOss/OpenGL/DrawableList.h"
#include "YolonaOss/Camera/CameraSystem.h"
#include "YolonaOss/Camera/FreeCamera.h"
#include "YolonaOss/Camera/RTSCamera.h"
#include "YolonaOss/Camera/FollowCamera.h"
#include "Protagonist.h"
#include "GameConfiguration.h"
#include "ScriptAPI.h"
#include "HaasScriptingLib/ScriptEngine.h"
#include "Context.h"
#include "BulletPool.h"
#include "UnitPool.h"
#include "Unit.h"
//#include "SuthanusPhysicsLib/SignedDistanceFunctionBullet.h"
#include "SCM.h"
#include "SCA.h"

#include <IyathuumCoreLib/lib/glm/gtc/matrix_transform.hpp>
#include "YolonaOss/Renderer/BoxRenderer.h"
#include "BulletDebugDrawer.h"

#include <iostream>

namespace Fatboy
{
  Fatboy::Fatboy()
  {
    std::string folder = "E:\\scmunpacked\\units\\UES0103";
    std::string a1 = "UES0103_A001.sca";
    SCA imp;
    imp.load(folder + "\\" + a1);
    _preDrawables = std::make_shared< YolonaOss::GL::DrawableList>();
    _postDrawables = std::make_shared< YolonaOss::GL::DrawableList>();
    _preDrawables->addDrawable(std::make_shared<YolonaOss::Background>());
    _postDrawables->addDrawable(std::make_shared<YolonaOss::FPS>());
    //_preDrawables->addDrawable(std::make_shared<YolonaOss::Ground>());
    _cam = std::make_shared<YolonaOss::Camera::CameraSystem>();
    _context = std::make_shared<Context>();

    initPhysic();
    _protagonist = std::make_shared<Protagonist>(_context,&_drawDebug, _cam);
    //initEnemys();
    _context->physic()->setDebugDrawer(new BulletDebugDrawer());
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
    auto tank = std::make_shared<Unit>(_context);
    tank->setStartPosition(glm::vec3(-3, 2, -3));
    tank->load(_spec);
    _context->units()->addUnit(tank);

    tank = std::make_shared<Unit>(_context);
    tank->setStartPosition(glm::vec3(3, 2, -3));
    tank->load(_spec);
    _context->units()->addUnit(tank);

    tank = std::make_shared<Unit>(_context);
    tank->setStartPosition(glm::vec3(3, 2, 3));
    tank->load(_spec);
    _context->units()->addUnit(tank);

    tank = std::make_shared<Unit>(_context);
    tank->setStartPosition(glm::vec3(-3, 2, 3));
    tank->load(_spec);
    _context->units()->addUnit(tank);
  }

  void Fatboy::update()
  {
    _cam->update();
    _protagonist->update();
    _context->physic()->update();
  }

  void Fatboy::load(YolonaOss::GL::DrawSpecification* spec)
  {
    _cam->load(spec);
    _cam->setCurrentCam("FollowCamera");  
    YolonaOss::Camera::FollowCamera::setTarget({ _protagonist });
    _protagonist->load(spec);
    _preDrawables->load(spec);
    _postDrawables->load(spec);
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