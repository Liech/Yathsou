#pragma once

#include <memory>

//class Fervor : public YolonaOss::GL::Drawable, public YolonaOss::GL::Updateable
//{
//public:
//  Fervor();
//  virtual void load(YolonaOss::GL::DrawSpecification*) override;
//  virtual void update() override;
//  virtual void draw()   override;
//
//private:
//  bool _drawPhysicDebug = false;
//
//  std::shared_ptr<YolonaOss::GL::DrawableList>     _preDrawables ;
//  std::shared_ptr<YolonaOss::GL::DrawableList>     _postDrawables;
//  std::shared_ptr<YolonaOss::GL::UpdateableList>   _updateList   ;
//
//  std::shared_ptr<Suthanus::PhysicEngine>          _physic;
//
//  std::shared_ptr<MainCharacterVisualization     >      _mainCharVis      ;
//  std::shared_ptr<MainCharacter                  >      _mainChar         ;
//  std::shared_ptr<Athanah::BulletDebugDrawer     >      _physicDebugDrawer;
//  std::shared_ptr<Suthanus::Box                  >      _testBox          ;
//  std::shared_ptr<Suthanus::Box                  >      _testBox2         ;
//  std::shared_ptr<YolonaOss::Camera::Camera2D    >      _camera           ;
//
//};