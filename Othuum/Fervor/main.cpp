#include <iostream>

#include "IyathuumCoreLib/Singleton/Database.h"
#include "YolonaOss/OpenGL/Window.h"
#include "Fervor.h"

int main(int argc, char** argv) {
  std::cout << "wub wub" << std::endl;
  int width  =600;
  int height =600;
  YolonaOss::GL::Window w(width, height);
  Fervor f;

  bool init = false;

  w.Update = [&f,&init,&w]() {
    if (!init) {
      init = true;
      f.load(w.getSpec());
    }
    f.update();
    f.draw  ();
  };
  w.run();

  Iyathuum::DatabaseTerminator::terminateAll();
}