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
#include "YolonaOss/Camera/Camera2D.h"

#include "AthanahCommonLib/BulletDebugDrawer.h"
#include "AthanahCommonLib/BoxVisualization.h"

#include "IyathuumCoreLib/View2D.h"
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
  _camera            = std::make_shared< YolonaOss::Camera::Camera2D    >();
  
  _preDrawables ->addDrawable(std::make_shared<YolonaOss::Background>());
  _postDrawables->addDrawable(std::make_shared<YolonaOss::FPS>());

  //_preDrawables ->addDrawable(std::dynamic_pointer_cast<YolonaOss::GL::Drawable>(_mainCharVis));
  auto controller = std::make_shared<YolonaOss::DirectWASDController>(*_mainChar);
  auto physicDebugHotkey = std::make_shared<YolonaOss::Hotkey>(YolonaOss::GL::Key::KEY_F1, [this]() {_drawPhysicDebug = !_drawPhysicDebug; });
  _updateList->addUpdateable(physicDebugHotkey);
  _updateList->addUpdateable(controller);
  _physic->setDebugDrawer(_physicDebugDrawer.get());
  _testBox = _physic->newBox(glm::vec3(12, 12, 0), glm::vec3(5, 5, 1), true);
  auto boxVis = std::make_shared<Athanah::BoxVisualization>(_testBox, Iyathuum::Color(255,0,0));
  _preDrawables->addDrawable(boxVis);
}

void Fervor::load(YolonaOss::GL::DrawSpecification* spec)
{
  _updateList   ->load(spec);
  _preDrawables ->load(spec);
  _postDrawables->load(spec);  
  _camera->load(spec->getCam(), spec->getWindow());
  _camera->view().setView(Iyathuum::glmAABB<2>(glm::vec2(0,0),glm::vec2(60,60)));
}

void Fervor::update()
{
  _physic    ->update();
  _updateList->update();
  _camera    ->update();
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
