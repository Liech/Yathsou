#include <iostream>

#include "IyathuumCoreLib/Singleton/Database.h"
#include "AhwassaGraphicsLib/Window.h"

int main(int argc, char** argv) {
  int width  =800;
  int height =600;
  Ahwassa::Window w(width, height);

  w.Update = [&w]() {

  };
  w.run();

  Iyathuum::DatabaseTerminator::terminateAll();
}