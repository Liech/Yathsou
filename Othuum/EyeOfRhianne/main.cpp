#include <iostream>
#include <filesystem>

#include "IyathuumCoreLib/Singleton/Database.h"

#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Core/Camera.h"
#include "AhwassaGraphicsLib/PostProcessing/DeferredComposer.h"
#include "AhwassaGraphicsLib/Drawables/Background.h"
#include "AhwassaGraphicsLib/Drawables/FPS.h"
#include "AhwassaGraphicsLib/Widgets/Button.h"
#include "AhwassaGraphicsLib/Input/Input.h"
#include "AhwassaGraphicsLib/Input/FreeCamera.h"

#include "AthanahCommonLib/SupComModelFactory.h"
#include "AthanahCommonLib/SupComModel.h"
#include "AthanahCommonLib/SupComMeshRendererDef.h"
#include "AhwassaGraphicsLib/PostProcessing/Bloom.h"
#include "AthanahCommonLib/SupComMeshRendererDef.h"

#include "AezeselFileIOLib/STLWriter.h"
#include "AezeselFileIOLib/SupremeCommander/SCM.h"

#include "ListSelection.h"
#include "AthanahCommonLib/BlueprintFactory.h"
#include "AthanahCommonLib/Blueprint.h"
#include "AthanahCommonLib/BlueprintGeneral.h"


#include "UnitModelSelection.h"
#include "GraphicOptions.h"
#include "EyeOfRhianneConfiguration.h"

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
  std::unique_ptr<Ahwassa::Background> background;
  std::unique_ptr<Ahwassa::FPS       > fps;

  std::unique_ptr<UnitModelSelection > unitUI   ;
  std::unique_ptr<GraphicOptions     > graphicUI;

  std::unique_ptr<Athanah::SupComMeshRendererDef> renderer;
  std::shared_ptr<Ahwassa::DeferredComposer>      composer;
  std::shared_ptr<Ahwassa::Bloom>                 bloom;
  std::shared_ptr<Athanah::SupComMesh>            mesh;

  std::shared_ptr<Ahwassa::FreeCamera> freeCam;
  w.Startup = [&]() {
    bloom = std::make_shared<Ahwassa::Bloom>(&w, width, height);
    
    freeCam = std::make_shared<Ahwassa::FreeCamera>(w.camera(), w.input());
    w.camera()->setPosition(glm::vec3(20, 20, 20));
    w.input().addUIElement(freeCam.get());

    unitUI = std::make_unique<UnitModelSelection>(config.UnitPath,
      [&](std::string u) {
      mesh = std::make_shared<Athanah::SupComMesh>();
      mesh->model = unitUI->getCurrentModel();
      mesh->teamColor = Iyathuum::Color(rand() % 255, rand() % 255, rand() % 255);
      mesh->transformation = glm::translate(glm::mat4(1.0), glm::vec3(0, 0, 0));
      renderer->addMesh(mesh);
    },&w);

    graphicUI = std::make_unique<GraphicOptions>(&w);

    composer = std::make_shared<Ahwassa::DeferredComposer>(&w, width, height);

    fps = std::make_unique<Ahwassa::FPS>(&w);
    background = std::make_unique<Ahwassa::Background>(&w);

    renderer = std::make_unique<Athanah::SupComMeshRendererDef>(w.camera());
  };

  w.Update = [&]() {
    unitUI->update();
    if (mesh)
      mesh->animation = unitUI->getAnimation();

    composer->start();
    renderer->draw();
    composer->end();
    bloom->draw(composer->getResult(), composer->getRawTextures()[3], 1);

    background->draw();
   
    bloom->drawResult();

    unitUI->draw();
    graphicUI->draw();

    if (config.ShowFPS) 
     fps->draw();
  };
  w.run();

  Iyathuum::DatabaseTerminator::terminateAll();
}