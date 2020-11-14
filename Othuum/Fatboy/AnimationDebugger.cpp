#include "AnimationDebugger.h"

#include "YolonaOss/Drawables/FPS.h"
#include "YolonaOss/Drawables/Background.h"
#include "YolonaOss/Drawables/Ground.h"

#include "YolonaOss/OpenGL/DrawableList.h"
#include "YolonaOss/Camera/CameraSystem.h"
#include "YolonaOss/Camera/FreeCamera.h"

#include "YolonaOss/OpenGL/Keys.h"
#include "YolonaOss/OpenGL/DrawSpecification.h"
#include "YolonaOss/OpenGL/Window.h"

namespace Fatboy{
  AnimationDebugger::AnimationDebugger() {
    _preDrawables = std::make_shared< YolonaOss::GL::DrawableList>();
    _postDrawables = std::make_shared< YolonaOss::GL::DrawableList>();
    _preDrawables->addDrawable(std::make_shared<YolonaOss::Background>());
    _postDrawables->addDrawable(std::make_shared<YolonaOss::FPS>());
    _preDrawables->addDrawable(std::make_shared<YolonaOss::Ground>());
    _cam = std::make_shared<YolonaOss::Camera::CameraSystem>();
  }

  void AnimationDebugger::load(YolonaOss::GL::DrawSpecification* spec){
    _spec = spec;
    _preDrawables->load(spec);
    _postDrawables->load(spec);
    _cam->load(spec);
    _cam->setCurrentCam("None");
  }

  void AnimationDebugger::draw() {
    _preDrawables->draw();
    _postDrawables->draw();

  }

  void AnimationDebugger::update(){
    _cam->update();

    auto isPressed = [this](YolonaOss::GL::Key key) {
      return _spec->getWindow()->getKeyStatus(key) == YolonaOss::GL::KeyStatus::PRESS;
    };
    if (isPressed(YolonaOss::GL::Key::KEY_F2) && !_keyPressed)
    {
      if (_cam->getCurrentCam() == "None")
        _cam->setCurrentCam("FreeCamera");
      else
        _cam->setCurrentCam("None");
      _keyPressed = true;
    }
    else if (!isPressed(YolonaOss::GL::Key::KEY_F2)) 
      _keyPressed = false;
  }
}