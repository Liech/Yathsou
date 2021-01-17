#include <iostream>

#include "IyathuumCoreLib/Singleton/Database.h"
#include "YolonaOss/OpenGL/Window.h"

int main(int argc, char** argv) {
  std::cout << "wub wub" << std::endl;
  int width  =600;
  int height =600;
  YolonaOss::GL::Window w(width, height);

  w.Update = []() {
    
  };
  w.run();

  Iyathuum::DatabaseTerminator::terminateAll();
}