#include "RenderTriangle.h"

#include "../OpenGL/Window.h"
#include "../OpenGL/DrawableList.h"
#include "../OpenGL/DrawSpecification.h"
#include "BasicTriangle.h"
#include "../Drawables/Background.h"

namespace YolonaOss {
  void RenderTriangle::run() {
    GL::Window w(1920, 1080);

    GL::DrawableList list;
    list.addDrawable(std::make_shared<Background>());
    list.addDrawable(std::make_shared<BasicTriangle>());
    GL::DrawSpecification spec(&w);
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
}