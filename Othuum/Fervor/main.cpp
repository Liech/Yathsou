#include <iostream>

#include "IyathuumCoreLib/Singleton/Database.h"
#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Drawables/Background.h"

#include "AhwassaGraphicsLib/BasicRenderer/RectangleRenderer.h"


int main(int argc, char** argv) {
  int width  = 800;
  int height = 600;
  Ahwassa::Window w(width, height);
  Ahwassa::Background b(&w);

  std::unique_ptr<Ahwassa::RectangleRenderer> rect;
  w.Startup = [&w,&rect]() {
    rect = std::make_unique<Ahwassa::RectangleRenderer>(&w);
  };

  w.Update = [&w,&b,&rect]() {
    b.draw();
    rect->start();
    rect->drawRectangle(Iyathuum::glmAABB<2>(glm::vec2(50, 50), glm::vec2(100, 100)), Iyathuum::Color(128,20,69));
    rect->end();
  };
  w.run();

  Iyathuum::DatabaseTerminator::terminateAll();
}