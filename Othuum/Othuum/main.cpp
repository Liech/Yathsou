#include <iostream>
#include "YolonaOss/OpenGL/Window.h"
#include "YolonaOss/OpenGL/DrawableList.h"
#include "YolonaOss/OpenGL/DrawSpecification.h"
#include "YolonaOss/Drawables/Background.h"
#include "DrawCubes.h"
#include "YolonaOss/Camera/FreeCamera.h"
#include "YolonaOss/Camera/RTSCamera.h"
#include "YolonaOss/Camera/CameraSystem.h"
#include "YolonaOss/Drawables/FPS.h"
#include "YolonaOss/Drawables/Widgets/Button.h"
#include "YolonaOss/structs/Database.h"
#include "YolonaOss/Renderer/BoxRenderer.h"
#include "YolonaOss/Examples/Texture2Tree.h"
#include <filesystem>
#include "YolonaOss/OpenGL/DrawSpecification.h"
#include <glm/gtx/intersect.hpp>

using namespace YolonaOss;

int main() { 

  
  //int width = 800;
  //int height = 600;
  int width = 1920;
  int height = 1080;
  GL::Window w(width, height);


  std::shared_ptr<GL::DrawableList> list = std::make_shared<GL::DrawableList>();
  list->addDrawable(std::make_shared<Background>());
  //list->addDrawable(std::make_shared<DrawCubes>());
  //list->addDrawable(std::make_shared<Texture2Tree>());
  list->addDrawable(std::make_shared<FPS>());
  Database<std::shared_ptr<GL::Drawable>>::add(list, { "Main" });
  std::shared_ptr<Camera::CameraSystem> cam = std::make_shared<Camera::CameraSystem>();

  std::shared_ptr<Button> b = std::make_shared<Button>("FreeCam", BoundingBox2(glm::vec2(0, 0), glm::vec2(200, 50)), [cam]() {cam->setCurrentCam("FreeCamera"); });
  Database<std::shared_ptr<Widget>>::add(b, { "MouseClick" });
  list->addDrawable(b);

  Database<std::shared_ptr<GL::Updateable>>::add(cam, { "Main" });
  glm::vec3 start, end;
  std::function<void(double, double)> f = [&w, &start, &end, cam](double, double) {
    glm::vec3 pick = w.getSpec()->getCam()->getPickRay(&w);
    glm::vec3 pos = w.getSpec()->getCam()->getPosition();
    //end = start + pick + pick + pick;

    float distance = 0;
    bool intersects = glm::intersectRayPlane(pos,
      pick,
      glm::vec3(0,0,0),
      glm::vec3(0, 1, 0),
      distance
    );
    if (intersects)
      start = pos + pick * distance;
  };
  //Database < std::function<void(double, double)>*>::add(&f, { "MouseClick" });

  w.Update = [&w, &start,&end,f]() {
    f(0, 0);
    BoxRenderer::start();
    BoxRenderer::drawDot(start, glm::vec3(0.2f, 0.2f, 0.2f), glm::vec4(1, 1, 0, 1));
    //BoxRenderer::drawDot(end, glm::vec3(0.2f, 0.2f, 0.2f), glm::vec4(0.9, 1, 0, 1));
    //BoxRenderer::drawLine(start, end,0.1f, glm::vec4(0, 1, 0, 1));
    BoxRenderer::end();
  };
  w.run();
} 