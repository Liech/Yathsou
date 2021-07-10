#include <iostream>
#include <filesystem>

#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Drawables/Background.h"
#include "AhwassaGraphicsLib/Drawables/FPS.h"

void enforceWorkingDir(std::string exeDir) {
  const size_t last_slash_idx = exeDir.find_last_of("\\/");
  if (std::string::npos != last_slash_idx)
  {
    exeDir.erase(last_slash_idx + 1);
  }
  std::filesystem::current_path(exeDir);
}

int main(int argc, char** argv) {
  enforceWorkingDir(std::string(argv[0]));
  int width = 800;
  int height = 600;
  Ahwassa::Window w(width, height);

  Ahwassa::Background b(&w);
  std::unique_ptr<Ahwassa::FPS> fps;


  w.Startup = [&]() {
    fps = std::make_unique<Ahwassa::FPS>(&w);

  };

  w.Update = [&]() {

    b.draw();
    fps->draw();
  };
  w.run();

}