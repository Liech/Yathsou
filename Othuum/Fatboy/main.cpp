#include <iostream>

#include "IyathuumCoreLib/Singleton/Database.h"
#include "YolonaOss/OpenGL/Window.h"
#include "Fatboy.h"
#include "GameConfiguration.h"
#include "IyathuumCoreLib/Util/UpdateTimer.h"

int main(int argc, char** argv) {
  std::cout << "wub wub" << std::endl;

  int width  = Fatboy::GameConfiguration::instance().ScreenWidth;
  int height = Fatboy::GameConfiguration::instance().ScreenHeight;
  YolonaOss::GL::Window w(width, height);
  Fatboy::Fatboy game;
  bool init = false;

  Iyathuum::UpdateTimer updater([&game]() {
      game.update();    
    }
  , Fatboy::GameConfiguration::instance().TicksPerSecond);

  w.Update = [&game,&init,&w, &updater]() {
    if (!init) {
      init = true;
      game.load(w.getSpec());
      updater.setTicksPerSecond(Fatboy::GameConfiguration::instance().TicksPerSecond);//reset
    }
    updater.update();
    game.draw();
  };
  w.run();

  Iyathuum::DatabaseTerminator::terminateAll();
}