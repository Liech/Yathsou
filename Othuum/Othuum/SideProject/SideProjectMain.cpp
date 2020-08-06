#include "SideProjectMain.h"

#include "SuthanusPhysicsLib/PhysicTest.h"
#include "IyathuumCoreLib/Singleton/Database.h"
#include "YolonaOss/Renderer/BoxRenderer.h"
#include "YolonaOss/Renderer/SphereRenderer.h"
#include "YolonaOss/OpenGL/DrawableList.h"
#include "YolonaOss/Drawables/FPS.h"
#include "YolonaOss/Drawables/Background.h"
#include "YolonaOss/Camera/CameraSystem.h"
#include <IyathuumCoreLib/lib/glm/gtc/matrix_transform.hpp>

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
    _boxes.push_back(_phys->newBox(glm::vec3(0, -3, 0)  ,glm::vec3(10,0.2,10),false));
    _spheres.push_back(_phys->newSphere(glm::vec3(0, 4, 0.5), 0.5, true));
    _spheres.push_back(_phys->newSphere(glm::vec3(0, 5, 0.5), 0.5, true));
    _spheres.push_back(_phys->newSphere(glm::vec3(0, 6, 0.5), 0.5, true));
    _spheres.push_back(_phys->newSphere(glm::vec3(0, 7, 0.5), 0.5, true));
    _spheres.push_back(_phys->newSphere(glm::vec3(0, 8, 0.5), 0.5, true));
    _spheres.push_back(_phys->newSphere(glm::vec3(0, 9, 0.5), 0.5, true));

    _boxes.push_back(_phys->newBox(glm::vec3(-1, 4, 0.5), glm::vec3(1,1,1), true));
    _boxes.push_back(_phys->newBox(glm::vec3(-1, 5, 0.5), glm::vec3(1,1,1), true));
    _boxes.push_back(_phys->newBox(glm::vec3(-1, 6, 0.5), glm::vec3(1,1,1), true));
    _boxes.push_back(_phys->newBox(glm::vec3(-1, 7, 0.5), glm::vec3(1,1,1), true));
    _boxes.push_back(_phys->newBox(glm::vec3(-1, 8, 0.5), glm::vec3(1,1,1), true));
    _boxes.push_back(_phys->newBox(glm::vec3(-1, 9, 0.5), glm::vec3(1, 1, 1), true));
    
    _vehicle = _phys->newVehicle(glm::vec3(1,3,1));
  }

  void SideProjectMain::draw()
  {
    _vehicle->forward();
    _phys->update();
    _list->draw();
    YolonaOss::BoxRenderer::start();
    for (auto box : _boxes){
      glm::mat4 transform = box->getTransformation();      
      transform = glm::scale(transform, box->getSize());
      transform = glm::translate(transform, glm::vec3(-0.5, -0.5, -0.5));
      YolonaOss::BoxRenderer::draw(transform, glm::vec4(0, 0, 1, 1));
    }

    glm::mat4 transformVehicle = _vehicle->getTransformation();
    transformVehicle = glm::scale(transformVehicle, _vehicle->getSize());
    transformVehicle = glm::translate(transformVehicle, glm::vec3(-0.5, -0.5, -0.5));
    YolonaOss::BoxRenderer::draw(transformVehicle, glm::vec4(0, 0.4, 1, 1));
    YolonaOss::BoxRenderer::end();

    YolonaOss::SphereRenderer::start();
    for (auto sphere : _spheres) {
      glm::mat4 transform = sphere->getTransformation();
      transform = glm::scale(transform, glm::vec3(sphere->getRadius(),sphere->getRadius(),sphere->getRadius()));
      YolonaOss::SphereRenderer::draw(transform, glm::vec4(0, 0.4, 1, 1));
    }
    YolonaOss::SphereRenderer::end();

  }
}