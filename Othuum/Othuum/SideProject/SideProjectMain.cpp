#include "SideProjectMain.h"

#include "SuthanusPhysicsLib/PhysicTest.h"
#include "IyathuumCoreLib/Singleton/Database.h"
#include "YolonaOss/Renderer/BoxRenderer.h"
#include "YolonaOss/OpenGL/DrawableList.h"
#include "YolonaOss/Drawables/FPS.h"
#include "YolonaOss/Drawables/Background.h"
#include "YolonaOss/Camera/CameraSystem.h"

namespace SideProject
{
  void SideProjectMain::load(YolonaOss::GL::DrawSpecification* spec)
  {
    _list = std::make_shared<YolonaOss::GL::DrawableList>();
    _list->addDrawable(std::make_shared<YolonaOss::Background>());
    _list->addDrawable(std::make_shared<YolonaOss::FPS>());
    _list->load(spec);
    std::shared_ptr<YolonaOss::Camera::CameraSystem> cam = std::make_shared<YolonaOss::Camera::CameraSystem>();
    cam->load(spec);
    Iyathuum::Database<std::shared_ptr<YolonaOss::GL::Updateable>>::add(cam, { "Main" });
    _phys = std::make_shared<Suthanus::PhysicTest>();
    _phys->go();
    _box = _phys->newBox(glm::vec3(0, 0, 0));
  }

  void SideProjectMain::draw()
  {
    _phys->update();
    _list->draw();
    glm::vec3 pos = _box->getPosition();
    YolonaOss::BoxRenderer::start();
    YolonaOss::BoxRenderer::drawDot(pos, glm::vec3(0.1f), glm::vec4(0, 0, 1, 1));
    YolonaOss::BoxRenderer::end();
  }
}