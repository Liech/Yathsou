#include <iostream>

#include "IyathuumCoreLib/Singleton/Database.h"
#include "YolonaOss/OpenGL/Window.h"
#include "Fatboy.h"
#include "GameConfiguration.h"
#include "IyathuumCoreLib/Util/UpdateTimer.h"
#include "HaasScriptingLib/ScriptEngine.h"

int main(int argc, char** argv) {
  std::cout << "wub wub" << std::endl;
  //Haas::ScriptEngine s;
  //s.blubb();
  //s.registerAverage();
  //std::vector<Haas::any> erg = s.callScript("add", {Haas::any(10),Haas::any(10)}, { Haas::any::type::Int });
  //if (erg[0].get_int() != 20)
  //  throw std::runtime_error("Wahh");
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