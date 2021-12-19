#include <iostream>
#include <filesystem>

#include "IyathuumCoreLib/Singleton/Database.h"
#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Core/Camera.h"
#include "AhwassaGraphicsLib/Core/Renderer.h"
#include "AhwassaGraphicsLib/PostProcessing/DeferredComposer.h"
#include "AhwassaGraphicsLib/Drawables/Background.h"
#include "AhwassaGraphicsLib/Drawables/FPS.h"
#include "AhwassaGraphicsLib/GUI/UI.h"


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
  //int height = 1500;
  //int width = 2500;
  Ahwassa::Window w(width, height);

  std::string scPath = "C:\\Program Files (x86)\\Steam\\steamapps\\common\\Supreme Commander Forged Alliance";
  std::string mapPath = scPath + "\\maps";

  std::string soundPath = scPath + "\\sounds\\Interface";

  {
    Ahwassa::Background b(&w);
    std::unique_ptr<Ahwassa::FPS> fps;

    std::shared_ptr<Ahwassa::DeferredComposer> composer;
    std::shared_ptr<Ahwassa::BasicTexture2DRenderer> textureRenderer;
    std::shared_ptr<Ahwassa::BasicBoxRenderer> boxRenderer;
    std::unique_ptr<Ahwassa::UI> ui;

    w.Startup = [&]() {
      ui = std::make_unique<Ahwassa::UI>(&w);
      fps = std::make_unique<Ahwassa::FPS>(&w);
    };

    w.Update = [&]() {

      b.draw();

      ui->draw();

      fps->draw();
    };
    w.run();
  }
  Iyathuum::DatabaseTerminator::terminateAll();
}