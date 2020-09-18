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

#include <IyathuumCoreLib/lib/glm/gtc/matrix_transform.hpp>
#include "YolonaOss/Renderer/BoxRenderer.h"

namespace Fatboy
{
  Fatboy::Fatboy()
  {
    _preDrawables = std::make_shared< YolonaOss::GL::DrawableList>();
    _postDrawables = std::make_shared< YolonaOss::GL::DrawableList>();
    _preDrawables->addDrawable(std::make_shared<YolonaOss::Background>());
    _postDrawables->addDrawable(std::make_shared<YolonaOss::FPS>());
    _preDrawables->addDrawable(std::make_shared<YolonaOss::Ground>());
    _cam = std::make_shared<YolonaOss::Camera::CameraSystem>();

    initPhysic();
    _protagonist = std::make_shared<Protagonist>(_physic);
  }

  void Fatboy::initPhysic()
  {
    _physic = std::make_shared<Suthanus::PhysicEngine>();    
    _landscape = _physic->newBox(glm::vec3(0, 0, 0), glm::vec3(20, 0, 20), false);
  }

  void Fatboy::update()
  {
    _cam->update();
    _protagonist->update();
    _physic->update();
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
    drawLandscape();
    _protagonist->draw();
    _postDrawables->draw();
  }
}