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
#include "UnitModelSelection.h"
#include "AnimationSelection.h"
#include "AthanahCommonLib/BlueprintFactory.h"
#include "AthanahCommonLib/Blueprint.h"
#include "AthanahCommonLib/BlueprintGeneral.h"

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
  //int width = 1200;
  //int height = 900;
  int width = 1920;
  int height = 1080;

  Ahwassa::Window w(width, height);
  std::unique_ptr<Ahwassa::Background> background;
  std::unique_ptr<Ahwassa::FPS       > fps;

  std::unique_ptr<UnitModelSelection > unitModels;

  std::unique_ptr<Athanah::SupComMeshRendererDef> renderer;
  std::shared_ptr<Ahwassa::DeferredComposer> composer;
  std::shared_ptr<Ahwassa::Bloom> bloom;

  std::shared_ptr<Athanah::SupComMesh> mesh;

  std::shared_ptr<Ahwassa::FreeCamera> freeCam;
  w.Startup = [&]() {
    bloom = std::make_shared<Ahwassa::Bloom>(&w, width, height);
    
    freeCam = std::make_shared<Ahwassa::FreeCamera>(w.camera(), w.input());
    w.camera()->setPosition(glm::vec3(20, 20, 20));
    w.input().addUIElement(freeCam.get());

    unitModels = std::make_unique<UnitModelSelection>("Data\\units\\",
      [&](std::string u) {
      mesh = std::make_shared<Athanah::SupComMesh>();
      mesh->model = unitModels->getCurrentModel();
      mesh->teamColor = Iyathuum::Color(rand() % 255, rand() % 255, rand() % 255);
      mesh->transformation = glm::translate(glm::mat4(1.0), glm::vec3(0, 0, 0));
      renderer->addMesh(mesh);
    },&w);


    composer = std::make_shared<Ahwassa::DeferredComposer>(&w, width, height);

    fps = std::make_unique<Ahwassa::FPS>(&w);
    background = std::make_unique<Ahwassa::Background>(&w);

    renderer = std::make_unique<Athanah::SupComMeshRendererDef>(w.camera());
  };

  w.Update = [&]() {
    unitModels->update();
    if (mesh)
      mesh->animation = unitModels->getAnimation();

    composer->start();
    renderer->draw();
    composer->end();
    bloom->draw(composer->getResult(), composer->getRawTextures()[3], 1);

    background->draw();
   
    bloom->drawResult();

    unitModels->draw();

    fps->draw();
  };
  w.run();

  Iyathuum::DatabaseTerminator::terminateAll();
}