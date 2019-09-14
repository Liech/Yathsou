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
  list.addDrawable(std::make_shared<DrawCubes>());
  DrawSpecification spec(&w);
  spec.width = 1920;
  spec.height = 1080;


  w.Startup = [&list, &spec]() {
    list.load(&spec);
  };

  w.Update = [&list]() {
    list.draw();
  };

  w.run();
} 