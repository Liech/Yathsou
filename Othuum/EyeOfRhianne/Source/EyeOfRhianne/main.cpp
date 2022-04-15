#include <iostream>
#include <filesystem>
#include <functional>

#include "IyathuumCoreLib/Singleton/Database.h"

#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Core/Camera.h"
#include "AhwassaGraphicsLib/Drawables/FPS.h"
#include "AhwassaGraphicsLib/Widgets/Button.h"
#include "AhwassaGraphicsLib/Input/Input.h"
#include "AhwassaGraphicsLib/Input/FreeCamera.h"
#include "AhwassaGraphicsLib/Uniforms/Texture.h"

#include "AthanahCommonLib/SupCom/SupComModel.h"
#include "AhwassaGraphicsLib/PostProcessing/Bloom.h"

#include "AezeselFileIOLib/STLWriter.h"
#include "AezeselFileIOLib/SupremeCommander/SCM.h"
#include "AezeselFileIOLib/ImageIO.h"

#include "ListSelection.h"

#include "AssetSelection.h"
#include "GraphicOptions.h"
#include "Graphic.h"
#include "EyeOfRhianneConfiguration.h"

#include "AezeselFileIOLib/SupremeCommander/SCMAP.h"

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

  EyeOfRhianneConfiguration config;
  config.fromJsonFile("Configuration.json");

  int width  = config.ScreenWidth;
  int height = config.ScreenHeight;

  Ahwassa::Window w(width, height);
  std::unique_ptr<Ahwassa::FPS       > fps;
  
  std::unique_ptr<AssetSelection>    assets   ;
  std::unique_ptr<Ahwassa::Button>   assetButton;
  std::unique_ptr<GraphicOptions>    graphicUI;
  std::unique_ptr<Graphic>           graphic;

  std::shared_ptr<Ahwassa::FreeCamera> freeCam;
  w.Startup = [&]() {
    
    freeCam = std::make_shared<Ahwassa::FreeCamera>(w.camera(), w.input(), Iyathuum::Key::MOUSE_BUTTON_1);
    w.camera()->setPosition(glm::vec3(20, 20, 20));
    w.input().addUIElement(freeCam.get(), 1);

    std::function<void()> disableAll = [&]() { 
      assets->setVisible(false);
      graphicUI->setVisible(false);
    };

    graphic = std::make_unique<Graphic>(&w);

    Iyathuum::glmAABB<2> assetArea      (glm::vec2(0, 0 ), glm::vec2(300, w.getHeight() - 50));
    Iyathuum::glmAABB<2> assetButtonArea(glm::vec2(0, w.getHeight() - 50), glm::vec2(300, 50));
    assets = std::make_unique<AssetSelection>(config,assetArea, *graphic);
    assetButton = std::make_unique<Ahwassa::Button>("Assets", assetButtonArea, [disableAll,&assets]() {
      bool vis = assets->isVisible();
      disableAll();
      assets->setVisible(!vis); 
    }, &w);

    graphicUI = std::make_unique<GraphicOptions>(disableAll,*graphic);

    fps = std::make_unique<Ahwassa::FPS>(&w);

  };

  w.Update = [&]() {
    assets->update();

    graphic->draw();

    assetButton->draw();
    assets->draw();
    graphicUI->drawUI();

    if (config.ShowFPS) 
     fps->draw();
  };
  w.run();

  Iyathuum::DatabaseTerminator::terminateAll();
}