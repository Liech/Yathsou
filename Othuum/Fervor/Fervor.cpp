#include "Fervor.h"

#include "MainCharacter.h"
#include "MainCharacterVisualization.h"

#include "YolonaOss/OpenGL/DrawableList.h"
#include "YolonaOss/OpenGL/UpdateableList.h"
#include "YolonaOss/Drawables/FPS.h"
#include "YolonaOss/Drawables/Background.h"
#include "YolonaOss/Input/DirectWASDController.h"
#include "YolonaOss/Input/Hotkey.h"
#include "YolonaOss/Renderer/BoxRenderer.h"
#include "YolonaOss/Camera/CameraSystem.h"

#include "AthanahCommonLib/BulletDebugDrawer.h"
#include "AthanahCommonLib/BoxVisualization.h"

#include "SuthanusPhysicsLib/PhysicEngine.h"

Fervor::Fervor()
{
  _preDrawables      = std::make_shared< YolonaOss::GL::DrawableList    >();
  _postDrawables     = std::make_shared< YolonaOss::GL::DrawableList    >();
  _updateList        = std::make_shared< YolonaOss::GL::UpdateableList  >();
  _mainChar          = std::make_shared< MainCharacter                  >();
  _mainCharVis       = std::make_shared< MainCharacterVisualization     >(*_mainChar);
  _physic            = std::make_shared< Suthanus::PhysicEngine         >();
  _physicDebugDrawer = std::make_shared< Athanah::BulletDebugDrawer     >();
  _camera            = std::make_shared< YolonaOss::Camera::CameraSystem>();

  _preDrawables ->addDrawable(std::make_shared<YolonaOss::Background>());
  _postDrawables->addDrawable(std::make_shared<YolonaOss::FPS>());

  //_preDrawables ->addDrawable(std::dynamic_pointer_cast<YolonaOss::GL::Drawable>(_mainCharVis));
  auto controller = std::make_shared<YolonaOss::DirectWASDController>(*_mainChar);
  auto physicDebugHotkey = std::make_shared<YolonaOss::Hotkey>(YolonaOss::GL::Key::KEY_F1, [this]() {_drawPhysicDebug = !_drawPhysicDebug; });
  _updateList->addUpdateable(physicDebugHotkey);
  _updateList->addUpdateable(controller);
  _updateList->addUpdateable(_camera);
  _physic->setDebugDrawer(_physicDebugDrawer.get());
  _testBox  = _physic->newBox(glm::vec3(120, 120, 0), glm::vec3(400, 50, 1), false);
  _testBox2 = _physic->newBox(glm::vec3(320, 320, 0), glm::vec3(50, 50, 1), true);
  auto boxVis = std::make_shared<Athanah::BoxVisualization>(_testBox, Iyathuum::Color(255, 0, 0));
  _preDrawables->addDrawable(boxVis);
  auto boxVis2 = std::make_shared<Athanah::BoxVisualization>(_testBox2, Iyathuum::Color(255, 0, 0));
  _preDrawables->addDrawable(boxVis2);
}

void Fervor::load(YolonaOss::GL::DrawSpecification* spec)
{
  _updateList   ->load(spec);
  _preDrawables ->load(spec);
  _postDrawables->load(spec);  

  _camera->setCurrentCam("Camera2D");
}

void Fervor::update()
{
  _physic    ->update();
  _updateList->update();
}

void Fervor::draw()
{
  _preDrawables->draw();
  _postDrawables->draw();
  if (_drawPhysicDebug){
    YolonaOss::BoxRenderer::start();
    _physic->debugDrawWorld();
    YolonaOss::BoxRenderer::end();
  }
}
