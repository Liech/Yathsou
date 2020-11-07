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
#include "YolonaOss/Renderer/MeshRenderer.h"
#include "YolonaOss/Util/ImageIO.h"
#include "YolonaOss/Renderer/TextureRenderer.h"
#include "YolonaOss/Renderer/SupComModelRenderer.h"
#include "YolonaOss/OpenGL/SupComVertex.h"
#include "SupComModel.h"
#include <iostream>

namespace Fatboy
{
  Fatboy::Fatboy()
  {
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
    //_land = _context->physic()->newHeightMap(glm::vec3(0, 2, 0));
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

    loadSupComModel();
    //loadLandscapeModel();
  }

  void Fatboy::loadLandscapeModel()
  {
    auto landscapeMesh = _land->getMesh();

    std::vector<YolonaOss::GL::PositionNormalVertex> vertices;
    std::vector<int>                                 indices;
    for (int i = 0; i < landscapeMesh.vertecies.size(); i++)
      vertices.push_back(YolonaOss::GL::PositionNormalVertex(landscapeMesh.vertecies[i], landscapeMesh.normals[i]));
    for (int i = 0; i < landscapeMesh.indices.size(); i++)
    {
      indices.push_back(landscapeMesh.indices[i]);
    }
    _mesh = new YolonaOss::Mesh(vertices, indices);
  }

  void Fatboy::loadSupComModel()
  {
    std::string folder = "E:\\scmunpacked\\units\\UAL0401";
    std::string a1 = "UAL0401_lod0.scm";
    std::string texture = "UAL0401_Albedo.dds";
    std::string mapdds = "C:\\Users\\Niki\\Documents\\My Games\\Gas Powered Games\\Supreme Commander Forged Alliance\\Maps\\Setons 10x10\\setons 10x10.dds";
    SCM imp;
    _modl = std::make_shared<SupComModel>(folder);

    std::vector<YolonaOss::GL::PositionNormalVertex> vertices;
    std::vector<YolonaOss::GL::SupComVertex> verticesT;
    std::vector<int>                                 indices;
    for (int i = 0; i < _modl->_model->vertecies.size(); i++) {
      vertices .push_back(YolonaOss::GL::PositionNormalVertex(_modl->_model->vertecies[i].position, _modl->_model->vertecies[i].normal));
      YolonaOss::GL::SupComVertex v;
      auto vPre = _modl->_model->vertecies[i];
      v.position = vPre.position;
      v.tangent  = vPre.tangent ;
      v.normal   = vPre.normal  ;
      v.binormal = vPre.binormal;
      v.uv1      = vPre.uv1     ;
      v.uv2      = vPre.uv2     ;
      verticesT.push_back(v);
    }
    for (int i = 0; i < _modl->_model->indices.size(); i++)
    {
      indices.push_back(_modl->_model->indices[i].a);
      indices.push_back(_modl->_model->indices[i].b);
      indices.push_back(_modl->_model->indices[i].c);
    }
    _mesh = new YolonaOss::Mesh(vertices, indices);
    _scMesh = new YolonaOss::SupComGLMesh(verticesT, indices);
    _scMesh->setAlbedo(_modl->_albedo);
    _scMesh->setInfo  (_modl->_info);
    _scMesh->setNormal(_modl->_normal);
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

    if (_mesh)
    {
      //YolonaOss::MeshRenderer::start();
      //YolonaOss::MeshRenderer::draw(*_mesh, glm::scale(glm::mat4(1.0), glm::vec3(0.1f, 0.1f, 0.1f)), glm::vec4(1, 0, 0, 1));
      //YolonaOss::MeshRenderer::end();
      YolonaOss::SupComModelRenderer::start();
      YolonaOss::SupComModelRenderer::draw(*_scMesh, glm::scale(glm::mat4(1.0), glm::vec3(0.1f, 0.1f, 0.1f)));
      YolonaOss::SupComModelRenderer::end();
      //YolonaOss::TextureRenderer::start();
      //YolonaOss::TextureRenderer::drawTexture(&(*(_modl->_albedo)), glm::scale(glm::mat4(1.0),glm::vec3(40, 40, 40)));
      //YolonaOss::TextureRenderer::end();
    }

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