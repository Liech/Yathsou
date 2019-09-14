#include <iostream>
#include "YolonaOss/OpenGL/Window.h"
#include "YolonaOss/OpenGL/DrawableList.h"
#include "YolonaOss/OpenGL/DrawSpecification.h"
#include "YolonaOss/Drawables/Background.h"
#include "DrawCubes.h"
int main() { 
  Window w(1920, 1080);

  DrawableList list;
  list.addDrawable(std::make_shared<Background>());
  DrawSpecification spec(&w);
  spec.width = 1920;
  spec.height = 1080;

  std::shared_ptr<Camera> camera;
  w.Startup = [&list, &spec, &camera]() {  
    camera = std::make_shared<Camera>("Camera", spec.width, spec.height);
    list.addDrawable(std::make_shared<DrawCubes>(camera));

    list.load(&spec);
  };

  w.Update = [&list, &camera, &w]() {  
    float radius = 4.0f;
    float camX = sin(w.getTime()) * radius;
    float camZ = cos(w.getTime()) * radius;
    camera->setPosition(glm::vec3(camX, 4,camZ));
    list.draw();
  };

  w.run();
} 