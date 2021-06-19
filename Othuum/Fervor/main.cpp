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
#include "AhwassaGraphicsLib/Vertex/PositionColorNormalVertex.h"

#include <IyathuumCoreLib/lib/glm/gtc/matrix_transform.hpp>

#include "AhwassaGraphicsLib/Util.h"
#include "AthanahCommonLib/Map/MapFactory.h"
#include "AthanahCommonLib/Map/Map.h"
#include "AthanahCommonLib/Map/MapRenderer.h"
#include "AezeselFileIOLib/ImageIO.h"
#include "AezeselFileIOLib/XSB.h"

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
  //int width = 800;
  //int height = 600;
  int height = 1500;
  int width = 2500;
  Ahwassa::Window w(width, height);

  std::string scPath = "C:\\Program Files (x86)\\Steam\\steamapps\\common\\Supreme Commander Forged Alliance";
  std::string mapPath = scPath + "\\maps";

  std::string soundPath = scPath + "\\sounds\\Interface.xsb";
  Aezesel::XSB xsbReader;
  for (auto s : xsbReader.load(soundPath))
    std::cout << s << std::endl;

  auto factory = std::make_shared<Athanah::MapFactory>(mapPath);
  std::string setons = "SCMP_009";
  std::string fields = "SCMP_015";
  std::string shards = "X1MP_010";
  auto map = factory->loadMap(setons);
  map->loadFull();

  for (auto x : map->scmap().terrainTexturePaths)
    std::cout << x.path << std::endl;

  auto& tex = map->scmap().highTexture;

  {  //better context for window
    Ahwassa::Background b(&w);
    std::unique_ptr<Ahwassa::FPS> fps;

    std::shared_ptr<Ahwassa::FreeCamera> freeCam;
    std::shared_ptr<Ahwassa::DeferredComposer> composer;
    std::shared_ptr<Ahwassa::BasicTexture2DRenderer> textureRenderer;
    std::shared_ptr<Ahwassa::IMesh> m;
    std::shared_ptr<Athanah::MapRenderer> mapRenderer;

    w.Startup = [&]() {
      composer = std::make_shared<Ahwassa::DeferredComposer>(&w, width, height);
      textureRenderer = std::make_shared< Ahwassa::BasicTexture2DRenderer>(&w);

      std::array<std::shared_ptr<Ahwassa::Texture>, 5> textures;
      for (int i = 0; i < 5; i++) {
        std::string path = "Data" + map->scmap().terrainTexturePaths[i].path;
        auto img = Aezesel::ImageIO::readImage(path);
        textures[i] = std::make_shared<Ahwassa::Texture>("TerrainTexture" + std::to_string(i), img.get());
      }

      mapRenderer = std::make_shared<Athanah::MapRenderer>(w.camera(),textures);

      auto tinter = [&](const std::array<size_t,2> position, Ahwassa::PositionColorNormalVertex& v) {
        std::array<size_t, 2> half = {position[0]/2,position[1]/2};
        if (position[0] == map->scmap().heightMapData->getDimension(0) - 1) half[0] = (position[0] - 1) / 2;
        if (position[1] == map->scmap().heightMapData->getDimension(1) - 1) half[1] = (position[1] - 1) / 2;
        v.color = map->scmap().highTexture->getVal(half).to4();
      };

      m = Ahwassa::HeightFieldMeshGenerator::generate<unsigned short, Ahwassa::PositionColorNormalVertex>(*map->scmap().heightMapData, 0, std::numeric_limits<unsigned short>().max(),tinter, 2000, 1);
      //w.renderer().mesh().addMesh(m);
      
      freeCam = std::make_shared<Ahwassa::FreeCamera>(w.camera(), w.input());
      w.input().addUIElement(freeCam.get());
      fps = std::make_unique<Ahwassa::FPS>(&w);
    };

    w.Update = [&]() {

      //composer->start();
      b.draw();
      //w.renderer().draw();
      mapRenderer->draw(*m);
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