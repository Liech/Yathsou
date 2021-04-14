#include <iostream>
#include <filesystem>

#include "IyathuumCoreLib/Singleton/Database.h"
#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Core/Camera.h"
#include "AhwassaGraphicsLib/Drawables/Background.h"
#include "AhwassaGraphicsLib/Drawables/FPS.h"

#include "AhwassaGraphicsLib/Input/Input.h"
#include "AhwassaGraphicsLib/Input/FreeCamera.h"

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
  //int width = 1920;
  //int height = 1080;
  
  Ahwassa::Window w(width, height);
  std::unique_ptr<Ahwassa::Background> background;
  std::unique_ptr<Ahwassa::FPS       > fps;

  std::shared_ptr<Ahwassa::FreeCamera> freeCam;
  w.Startup = [&]() {
    freeCam = std::make_shared<Ahwassa::FreeCamera>(w.camera(), w.input());
    w.input().addUIElement(freeCam.get());
    fps = std::make_unique<Ahwassa::FPS>(&w);
    background = std::make_unique<Ahwassa::Background>(&w);
  };

  w.Update = [&]() {
    background->draw();

    fps->draw();
  };
  w.run();

  Iyathuum::DatabaseTerminator::terminateAll();
}