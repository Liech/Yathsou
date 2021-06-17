#include <iostream>
#include <filesystem>

#include "IyathuumCoreLib/Singleton/Database.h"
#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Core/Camera.h"
#include "AhwassaGraphicsLib/Core/Renderer.h"
#include "AhwassaGraphicsLib/PostProcessing/DeferredComposer.h"
#include "AhwassaGraphicsLib/Drawables/Background.h"
#include "AhwassaGraphicsLib/Drawables/FPS.h"
#include "AhwassaGraphicsLib/Input/Input.h"
#include "AhwassaGraphicsLib/Input/FreeCamera.h"
#include "AhwassaGraphicsLib/Input/FileDropper.h"
#include "AhwassaGraphicsLib/BasicRenderer/BasicTexture2DRenderer.h"
#include "AhwassaGraphicsLib/Renderer/DiffuseMeshRenderer.h"
#include "AhwassaGraphicsLib/BufferObjects/FBO.h"
#include "AhwassaGraphicsLib/Geometry/HeightFieldMeshGenerator.h"

#include <IyathuumCoreLib/lib/glm/gtc/matrix_transform.hpp>

#include "AhwassaGraphicsLib/Util.h"
#include "AthanahCommonLib/Map/MapFactory.h"
#include "AthanahCommonLib/Map/Map.h"

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

  std::string mapPath = "C:\\Program Files (x86)\\Steam\\steamapps\\common\\Supreme Commander Forged Alliance\\maps";

  auto factory = std::make_shared<Athanah::MapFactory>(mapPath);
  auto map = factory->loadMap("SCMP_009");
  map->loadFull();



  {  //better context for window
    Ahwassa::Background b(&w);
    std::unique_ptr<Ahwassa::FPS> fps;

    std::shared_ptr<Ahwassa::FreeCamera> freeCam;
    std::shared_ptr<Ahwassa::DeferredComposer> composer;
    std::shared_ptr<Ahwassa::BasicTexture2DRenderer> textureRenderer;
    std::shared_ptr<Ahwassa::IMesh> m;
    std::shared_ptr< Ahwassa::DiffuseMeshRendererMesh> mesh;

    w.Startup = [&]() {
      composer = std::make_shared<Ahwassa::DeferredComposer>(&w, width, height);
      textureRenderer = std::make_shared< Ahwassa::BasicTexture2DRenderer>(&w);

      mesh = std::make_shared< Ahwassa::DiffuseMeshRendererMesh>();
      mesh->mesh = Ahwassa::HeightFieldMeshGenerator::generate<unsigned short>(*map->scmap().heightMapData, 0, std::numeric_limits<unsigned short>().max(), 2000, 1);
      w.renderer().mesh().addMesh(mesh);
      
      freeCam = std::make_shared<Ahwassa::FreeCamera>(w.camera(), w.input());
      w.input().addUIElement(freeCam.get());
      fps = std::make_unique<Ahwassa::FPS>(&w);
    };

    w.Update = [&]() {

      //composer->start();
      b.draw();
      w.renderer().draw();
      //composer->end();

      //textureRenderer->start();
      //textureRenderer->draw(*composer->getResult(), glm::vec2(0),glm::vec2(width,height));
      //textureRenderer->end();

      fps->draw();
    };
    w.run();
  }
  Iyathuum::DatabaseTerminator::terminateAll();
}