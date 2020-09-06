#include "Fatboy.h"

#include "SuthanusPhysicsLib/PhysicTest.h"
#include "YolonaOss/Drawables/FPS.h"
#include "YolonaOss/Drawables/Background.h"
#include "YolonaOss/Drawables/Ground.h"
#include "YolonaOss/OpenGL/DrawableList.h"
#include "YolonaOss/Camera/CameraSystem.h"
#include "YolonaOss/Camera/FreeCamera.h"
#include "YolonaOss/Camera/RTSCamera.h"
#include "YolonaOss/Camera/FollowCamera.h"
#include "Protagonist.h"

namespace Fatboy
{
  Fatboy::Fatboy()
  {
    _drawables = std::make_shared< YolonaOss::GL::DrawableList>();
    _drawables->addDrawable(std::make_shared<YolonaOss::Background>());
    _drawables->addDrawable(std::make_shared<YolonaOss::FPS>());
    _drawables->addDrawable(std::make_shared<YolonaOss::Ground>());
    _cam = std::make_shared<YolonaOss::Camera::CameraSystem>();
    _protagonist = std::make_shared<Protagonist>();

    initPhysic();
  }

  void Fatboy::initPhysic()
  {
    _physic = std::make_shared<Suthanus::PhysicTest>();    
  }

  void Fatboy::update()
  {
    _cam->update();
    _protagonist->update();
  }

  void Fatboy::load(YolonaOss::GL::DrawSpecification* spec)
  {
    _cam->load(spec);
    _cam->setCurrentCam("FollowCamera");  
    YolonaOss::Camera::FollowCamera::setTarget({ _protagonist });
    _protagonist->load(spec);
    _drawables->load(spec);
  }

  void Fatboy::draw()
  {
    _drawables  ->draw();
    _protagonist->draw();
  }
}