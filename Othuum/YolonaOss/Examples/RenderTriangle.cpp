#include "RenderTriangle.h"

#include "../OpenGL/Window.h"
#include "../OpenGL/DrawableList.h"
#include "../OpenGL/DrawSpecification.h"
#include "BasicTriangle.h"
#include "../Drawables/Background.h"
#include "IyathuumCoreLib/Singleton/Database.h"

namespace YolonaOss {
  void RenderTriangle::run() {
    GL::Window w(1920, 1080);

    std::shared_ptr<GL::DrawableList> list = std::make_shared<GL::DrawableList>();
    list->addDrawable(std::make_shared<Background>());
    list->addDrawable(std::make_shared<BasicTriangle>());
    Iyathuum::Database<std::shared_ptr<GL::Drawable>>::add(list, { "Main" });

    w.run();
  }
}