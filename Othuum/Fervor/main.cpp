#include <iostream>

#include "IyathuumCoreLib/Singleton/Database.h"
#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Drawables/Background.h"

#include "AhwassaGraphicsLib/BasicRenderer/RectangleRenderer.h"
#include "AhwassaGraphicsLib/Graphics/Rectangles.h"
#include "AhwassaGraphicsLib/Graphics/Rectangle.h"


int main(int argc, char** argv) {
  int width  = 800;
  int height = 600;
  Ahwassa::Window w(width, height);
  Ahwassa::Background b(&w);

  std::vector<std::shared_ptr<Ahwassa::Rectangle>> handle;

  std::unique_ptr<Ahwassa::Rectangles> g;
  w.Startup = [&]() {
    g = std::make_unique<Ahwassa::Rectangles>(&w);

    for (int i = 0; i < 10000; i++) {
      auto rec = Iyathuum::glmAABB<2>(glm::vec2(rand() % width, rand() % height), glm::vec2(rand()%10+10, rand()%10+10));
      auto clr = Iyathuum::Color(rand()%255, rand() % 255, rand() % 255);
      handle.push_back(g->newRectangle(rec, clr));
    }
  };

  w.Update = [&]() {

    for (int i = 0; i < 10000; i++) {
      auto rec = Iyathuum::glmAABB<2>(glm::vec2(rand() % width, rand() % height), glm::vec2(rand() % 10 + 10, rand() % 10 + 10));
      auto clr = Iyathuum::Color(rand() % 255, rand() % 255, rand() % 255);
      handle[i]->location = rec;
    }

    b.draw();
    g->draw();
  };
  w.run();

  Iyathuum::DatabaseTerminator::terminateAll();
}