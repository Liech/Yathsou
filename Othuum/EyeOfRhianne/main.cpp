#include <iostream>
#include <filesystem>
#include <functional>

#include "IyathuumCoreLib/Singleton/Database.h"

#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Core/Camera.h"
#include "AhwassaGraphicsLib/Core/Renderer.h"
#include "AhwassaGraphicsLib/PostProcessing/DeferredComposer.h"
#include "AhwassaGraphicsLib/Drawables/Background.h"
#include "AhwassaGraphicsLib/Drawables/FPS.h"
#include "AhwassaGraphicsLib/Widgets/Button.h"
#include "AhwassaGraphicsLib/Input/Input.h"
#include "AhwassaGraphicsLib/Input/FreeCamera.h"
#include "AhwassaGraphicsLib/Uniforms/Texture.h"
#include "AhwassaGraphicsLib/BasicRenderer/BasicTexture2DRenderer.h"

#include "AthanahCommonLib/SupComModelFactory.h"
#include "AthanahCommonLib/SupComModel.h"
#include "AthanahCommonLib/SupComMeshRendererDef.h"
#include "AhwassaGraphicsLib/PostProcessing/Bloom.h"
#include "AthanahCommonLib/SupComMeshRendererDef.h"

#include "AezeselFileIOLib/STLWriter.h"
#include "AezeselFileIOLib/SupremeCommander/SCM.h"
#include "AezeselFileIOLib/ImageIO.h"

#include "ListSelection.h"
#include "AthanahCommonLib/BlueprintFactory.h"
#include "AthanahCommonLib/Blueprint.h"
#include "AthanahCommonLib/BlueprintGeneral.h"

#include "AthanahCommonLib/SkyBox.h"

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
  std::shared_ptr<Athanah::SkyBox>                skyBox;
  std::shared_ptr<Ahwassa::Texture>               skyTexture;

  std::string skyFolder = "Data\\textures\\environment";
  std::string skyFile = "DefaultEnvCube.dds";


  std::shared_ptr<Ahwassa::FreeCamera> freeCam;
  w.Startup = [&]() {
    bloom = std::make_shared<Ahwassa::Bloom>(&w, width, height);
    
    freeCam = std::make_shared<Ahwassa::FreeCamera>(w.camera(), w.input());
    w.camera()->setPosition(glm::vec3(20, 20, 20));
    w.input().addUIElement(freeCam.get());

    std::function<void()> disableAll = [&]() { 
      unitUI->setVisible(false);
      graphicUI->setVisible(false);
    };

    unitUI = std::make_unique<UnitModelSelection>(config.UnitPath, disableAll,
      [&](std::string u) {
      mesh = std::make_shared<Athanah::SupComMesh>();
      mesh->model = unitUI->getCurrentModel();
      mesh->teamColor = Iyathuum::Color(rand() % 255, rand() % 255, rand() % 255);
      mesh->transformation = glm::translate(glm::mat4(1.0), glm::vec3(0, 0, 0));
      renderer->addMesh(mesh);
    },&w);

    composer = std::make_shared<Ahwassa::DeferredComposer>(&w, width, height);

    std::vector<std::shared_ptr<Ahwassa::Texture>> textures;
    textures.push_back(bloom->getResult());
    textures.push_back(composer->getResult());
    for (auto x : composer->getRawTextures())
      textures.push_back(x);
    textures.push_back(composer->getDepth());

    graphicUI = std::make_unique<GraphicOptions>(textures,bloom,disableAll,&w);


    fps = std::make_unique<Ahwassa::FPS>(&w);
    background = std::make_unique<Ahwassa::Background>(&w);

    renderer = std::make_unique<Athanah::SupComMeshRendererDef>(w.camera());

    if (std::filesystem::exists(skyFolder + "\\" + skyFile)) {
      auto img = Aezesel::ImageIO::readImage(skyFolder + "\\" + skyFile);
      skyTexture = std::make_shared <Ahwassa::Texture>("Sky", img.get());
      skyBox = std::make_shared<Athanah::SkyBox>(skyTexture, w.camera());
    }
  };

  w.Update = [&]() {
    unitUI->update();
    if (mesh)
      mesh->animation = unitUI->getAnimation();

    composer->start();
    if(skyBox) 
      skyBox->draw();
    renderer->draw();
    composer->end();
    bloom->draw(composer->getResult(), composer->getRawTextures()[3], 1);

    background->draw();

    w.renderer().texture().start();
    w.renderer().texture().draw(*graphicUI->getCurrentTexture(), Iyathuum::glmAABB<2>(glm::vec2(0, 0), glm::vec2(w.getWidth(), w.getHeight())),true);
    w.renderer().texture().end();

    unitUI->draw();
    graphicUI->drawUI();

    if (config.ShowFPS) 
     fps->draw();
  };
  w.run();

  Iyathuum::DatabaseTerminator::terminateAll();
}