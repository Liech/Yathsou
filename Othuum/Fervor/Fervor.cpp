#include "Fervor.h"

#include "MainCharacter.h"
#include "MainCharacterVisualization.h"

#include "YolonaOss/OpenGL/DrawableList.h"
#include "YolonaOss/OpenGL/UpdateableList.h"
#include "YolonaOss/Drawables/FPS.h"
#include "YolonaOss/Drawables/Background.h"
#include "YolonaOss/Input/DirectWASDController.h"
#include "YolonaOss/Input/Hotkey.h"

#include "SuthanusPhysicsLib/PhysicEngine.h"
#include "AthanahCommonLib/BulletDebugDrawer.h"

Fervor::Fervor()
{
  _preDrawables      = std::make_shared< YolonaOss::GL::DrawableList  >();
  _postDrawables     = std::make_shared< YolonaOss::GL::DrawableList  >();
  _updateList        = std::make_shared< YolonaOss::GL::UpdateableList>();
  _mainChar          = std::make_shared< MainCharacter                >();
  _mainCharVis       = std::make_shared< MainCharacterVisualization   >(*_mainChar);
  _physic            = std::make_shared< Suthanus::PhysicEngine       >();
  _physicDebugDrawer = std::make_shared< Athanah::BulletDebugDrawer   >();

  _preDrawables ->addDrawable(std::make_shared<YolonaOss::Background>());
  _postDrawables->addDrawable(std::make_shared<YolonaOss::FPS>());

  _preDrawables ->addDrawable(std::dynamic_pointer_cast<YolonaOss::GL::Drawable>(_mainCharVis));
  auto controller = std::make_shared<YolonaOss::DirectWASDController>(*_mainChar);
  auto physicDebugHotkey = std::make_shared<YolonaOss::Hotkey>(YolonaOss::GL::Key::KEY_F1, [this]() {_drawPhysicDebug = !_drawPhysicDebug; });
  _updateList->addUpdateable(physicDebugHotkey);
  _updateList->addUpdateable(controller);

  _physic->setDebugDrawer(_physicDebugDrawer.get());
}

void Fervor::load(YolonaOss::GL::DrawSpecification* spec)
{
  _updateList   ->load(spec);
  _preDrawables ->load(spec);
  _postDrawables->load(spec);  
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
    _physic->debugDrawWorld();
  }
}
