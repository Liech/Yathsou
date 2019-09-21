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
using namespace YolonaOss;

int main() { 
  int width = 1920;
  int height = 1080;
  GL::Window w(width, height);

  std::shared_ptr<Button> b = std::make_shared<Button>("Button", BoundingBox2(glm::vec2(400, 400), glm::vec2(200, 50)), []() {std::cout << "Hello!" << std::endl; });
  Database<std::shared_ptr<Widget>>::add(b, { "MouseClick" });

  std::shared_ptr<GL::DrawableList> list = std::make_shared<GL::DrawableList>();
  list->addDrawable(std::make_shared<Background>());
  list->addDrawable(std::make_shared<DrawCubes>());
  list->addDrawable(std::make_shared<FPS>());
  list->addDrawable(b);
  Database<std::shared_ptr<GL::Drawable>>::add(list, {"Main"});

  w.run();
} 