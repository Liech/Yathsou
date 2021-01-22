#include <iostream>

#include "IyathuumCoreLib/Singleton/Database.h"
#include "IyathuumCoreLib/Util/UpdateTimer.h"
#include "YolonaOss/OpenGL/Window.h"
#include "Fervor.h"

int main(int argc, char** argv) {
  int width  =600;
  int height =600;
  YolonaOss::GL::Window w(width, height);
  Fervor f;
  Iyathuum::UpdateTimer timer([&f]() {f.update(); },30);
  bool init = false;

  w.Update = [&f,&init,&w,&timer]() {
    if (!init) {
      init = true;
      f.load(w.getSpec());
    }
    timer.update();
    f.draw  ();
  };
  w.run();

  Iyathuum::DatabaseTerminator::terminateAll();
}