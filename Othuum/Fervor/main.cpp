#include <iostream>

#include "IyathuumCoreLib/Singleton/Database.h"
#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Drawables/Background.h"

#include "AhwassaGraphicsLib/BasicRenderer/RectangleRenderer.h"
#include "AhwassaGraphicsLib/Graphics/Rectangles.h"


int main(int argc, char** argv) {
  int width  = 800;
  int height = 600;
  Ahwassa::Window w(width, height);
  Ahwassa::Background b(&w);

  auto rec = Iyathuum::glmAABB<2>(glm::vec2(50, 50), glm::vec2(100, 100));
  auto clr = Iyathuum::Color(128, 20, 69);
  std::shared_ptr<Ahwassa::Rectangle> handle;

  std::unique_ptr<Ahwassa::RectangleRenderer> rect;
  std::unique_ptr<Ahwassa::Rectangles> g;
  w.Startup = [&]() {
    rect = std::make_unique<Ahwassa::RectangleRenderer>(&w);
    g = std::make_unique<Ahwassa::Rectangles>(&w);

    handle = g->newRectangle(rec, clr);
  };

  w.Update = [&]() {
    b.draw();
    g->draw();
    //rect->start();
    //rect->drawRectangle(rec, clr);
    //rect->end();
  };
  w.run();

  Iyathuum::DatabaseTerminator::terminateAll();
}