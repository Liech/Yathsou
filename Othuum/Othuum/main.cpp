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
#include <filesystem>

using namespace YolonaOss;

int main() { 

  
  int width = 800;
  int height = 600;
  GL::Window w(width, height);


  std::shared_ptr<GL::DrawableList> list = std::make_shared<GL::DrawableList>();
  list->addDrawable(std::make_shared<Background>());
  list->addDrawable(std::make_shared<DrawCubes>());
  list->addDrawable(std::make_shared<FPS>());
  Database<std::shared_ptr<GL::Drawable>>::add(list, { "Main" });
  std::shared_ptr<Camera::CameraSystem> cam = std::make_shared<Camera::CameraSystem>();

  std::shared_ptr<Button> b = std::make_shared<Button>("FreeCam", BoundingBox2(glm::vec2(0, 0), glm::vec2(200, 50)), [cam]() {cam->setCurrentCam("FreeCamera"); });
  Database<std::shared_ptr<Widget>>::add(b, { "MouseClick" });
  list->addDrawable(b);

  Database<std::shared_ptr<GL::Updateable>>::add(cam, { "Main" });
  w.Update = []() {
    //BoxRenderer::start();
    //BoxRenderer::drawBox(glm::vec3(4,4,4),glm::vec3(4,4,4),glm::vec4(0,1,0,1));
    //BoxRenderer::end();
  };
  w.run();
} 