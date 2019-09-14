#include "RenderTriangle.h"

#include "../OpenGL/Window.h"
#include "../OpenGL/DrawableList.h"
#include "../OpenGL/DrawSpecification.h"
#include "BasicTriangle.h"
#include "../Drawables/Background.h"

void RenderTriangle::run() {
  Window w(1920, 1080);

  DrawableList list;
  list.addDrawable(std::make_shared<Background>());
  list.addDrawable(std::make_shared<BasicTriangle>());
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