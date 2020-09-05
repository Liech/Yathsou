#include <iostream>

#include "IyathuumCoreLib/Singleton/Database.h"
#include "YolonaOss/OpenGL/Window.h"
#include "Fatboy.h"

int main(int argc, char** argv) {
  std::cout << "wub wub" << std::endl;

  int width  = 1920;
  int height = 1080;
  YolonaOss::GL::Window w(width, height);
  Fatboy::Fatboy game;
  bool init = false;

  w.Update = [&game,&init,&w]() {
    if (!init) {
      init = true;
      game.load(w.getSpec());
    }
    game.update();
    game.draw();
  };
  w.run();

  Iyathuum::DatabaseTerminator::terminateAll();
}