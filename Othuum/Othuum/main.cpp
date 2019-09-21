#include <iostream>
#include "YolonaOss/OpenGL/Window.h"
#include "YolonaOss/OpenGL/DrawableList.h"
#include "YolonaOss/OpenGL/DrawSpecification.h"
#include "YolonaOss/Drawables/Background.h"
#include "DrawCubes.h"
#include "YolonaOss/Camera/FreeCamera.h"
#include "YolonaOss/Camera/RTSCamera.h"
#include "YolonaOss/Drawables/FPS.h"
#include "YolonaOss/Drawables/Widgets/Button.h"
#include "YolonaOss/structs/Database.h"
using namespace YolonaOss;
using namespace YolonaOss::GL;

int main() { 
  Window w(1920, 1080);

  DrawableList list;
  list.addDrawable(std::make_shared<Background>());
  DrawSpecification spec(&w);
  spec.width = 1920;
  spec.height = 1080;

  std::shared_ptr<Camera> camera;
  RTSCamera freeCam(&w);

  w.Startup = [&list, &spec, &camera,&freeCam]() {  
    camera = std::make_shared<Camera>("Camera", spec.width, spec.height);
    camera->setTarget(camera->getPosition() - glm::vec3(0, 0, 1));
    freeCam.load(camera);
    list.addDrawable(std::make_shared<DrawCubes>(camera));
    list.addDrawable(std::make_shared<FPS>());

    std::shared_ptr<Button> b = std::make_shared<Button>("Button", BoundingBox2(glm::vec2(400, 400), glm::vec2(200, 50)), []() {std::cout << "Hello!" << std::endl; });
    Database<std::shared_ptr<Widget>>::add(b, {"MouseClick"});
    list.addDrawable(b);

    list.load(&spec);
  };

  w.Update = [&list, &camera, &w, &freeCam]() {  
    float radius = 4.0f;
    //float camX = sin(w.getTime()) * radius;
    //float camZ = cos(w.getTime()) * radius;
    //camera->setPosition(glm::vec3(camX, 4,camZ));
    freeCam.update();
    list.draw();
    glm::vec3 dir = camera->getPosition() - camera->getTarget();
    //std::cout << dir.x << " " << dir.y << " " <<dir.z << std::endl;
  };

  w.run();
} 