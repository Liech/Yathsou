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
#include "AhwassaGraphicsLib/Renderer/BoxRenderer.h"
#include "AhwassaGraphicsLib/BasicRenderer/BasicBoxRenderer.h"
#include "AhwassaGraphicsLib/Renderer/Line.h"
#include "AhwassaGraphicsLib/BufferObjects/FBO.h"
#include "AhwassaGraphicsLib/Geometry/HeightFieldMeshGenerator.h"
#include "AhwassaGraphicsLib/Vertex/PositionColorNormalVertex.h"

#include <IyathuumCoreLib/lib/glm/gtc/matrix_transform.hpp>

#include "AhwassaGraphicsLib/Util.h"
#include "AthanahCommonLib/Map/MapFactory.h"
#include "AthanahCommonLib/Map/Map.h"
#include "AthanahCommonLib/Map/MapRenderer.h"
#include "AezeselFileIOLib/ImageIO.h"
#include "AezeselFileIOLib/Sound/XSB.h"
#include "AezeselFileIOLib/Sound/XWB.h"
#include "AezeselFileIOLib/Sound/SoundIO.h"
#include "IyathuumCoreLib/BaseTypes/Sound.h"
#include "AhwassaGraphicsLib/Sound/SoundEngine.h"
#include "IyathuumCoreLib/Tree/glmOctree.h"

void enforceWorkingDir(std::string exeDir) {
  const size_t last_slash_idx = exeDir.find_last_of("\\/");
  if (std::string::npos != last_slash_idx)
  {
    exeDir.erase(last_slash_idx + 1);
  }
  std::filesystem::current_path(exeDir);
}

void octree(std::shared_ptr<Ahwassa::BasicBoxRenderer>renderer, Iyathuum::glmOctree& tree) {
  for (const auto& d : tree.findSphere(tree.aabb().getCenter(),0.5f))
  //for (const auto& d : tree.dumpObj())
    renderer->drawDot(d->glmPosition(), glm::vec3(0.05f, 0.05f, 0.05f), Iyathuum::Color(255, 128, 0));
  return;
  for (const auto& d : tree.dumpAABB()) {
    float x = d.getSize()[0];
    float y = d.getSize()[1];
    float z = d.getSize()[2];
    float s = 0.01f;
  
    renderer->drawLine(d.getPosition() + glm::vec3(0,0,0), d.getPosition() + glm::vec3(0,0,z), s, Iyathuum::Color(255, 0, 0));
    renderer->drawLine(d.getPosition() + glm::vec3(x,0,0), d.getPosition() + glm::vec3(x,0,z), s, Iyathuum::Color(255, 0, 0));
    renderer->drawLine(d.getPosition() + glm::vec3(0,y,0), d.getPosition() + glm::vec3(0,y,z), s, Iyathuum::Color(255, 0, 0));
    renderer->drawLine(d.getPosition() + glm::vec3(x,y,0), d.getPosition() + glm::vec3(x,y,z), s, Iyathuum::Color(255, 0, 0));
  
    renderer->drawLine(d.getPosition() + glm::vec3(0, 0, 0), d.getPosition() + glm::vec3(0, y, 0), s, Iyathuum::Color(255, 0, 0));
    renderer->drawLine(d.getPosition() + glm::vec3(x, 0, 0), d.getPosition() + glm::vec3(x, y, 0), s, Iyathuum::Color(255, 0, 0));
    renderer->drawLine(d.getPosition() + glm::vec3(0, 0, z), d.getPosition() + glm::vec3(0, y, z), s, Iyathuum::Color(255, 0, 0));
    renderer->drawLine(d.getPosition() + glm::vec3(x, 0, z), d.getPosition() + glm::vec3(x, y, z), s, Iyathuum::Color(255, 0, 0));
  
    renderer->drawLine(d.getPosition() + glm::vec3(0, 0, 0), d.getPosition() + glm::vec3(x, 0, 0), s, Iyathuum::Color(255, 0, 0));
    renderer->drawLine(d.getPosition() + glm::vec3(0, y, 0), d.getPosition() + glm::vec3(x, y, 0), s, Iyathuum::Color(255, 0, 0));
    renderer->drawLine(d.getPosition() + glm::vec3(0, 0, z), d.getPosition() + glm::vec3(x, 0, z), s, Iyathuum::Color(255, 0, 0));
    renderer->drawLine(d.getPosition() + glm::vec3(0, y, z), d.getPosition() + glm::vec3(x, y, z), s, Iyathuum::Color(255, 0, 0));
  
  }
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

    std::shared_ptr<Ahwassa::FreeCamera> freeCam;
    std::shared_ptr<Ahwassa::DeferredComposer> composer;
    std::shared_ptr<Ahwassa::BasicTexture2DRenderer> textureRenderer;
    std::shared_ptr<Ahwassa::BasicBoxRenderer> boxRenderer;

    w.Startup = [&]() {
      composer = std::make_shared<Ahwassa::DeferredComposer>(&w, width, height);
      textureRenderer = std::make_shared< Ahwassa::BasicTexture2DRenderer>(&w);
      boxRenderer = std::make_shared<Ahwassa::BasicBoxRenderer>(w.camera());

      freeCam = std::make_shared<Ahwassa::FreeCamera>(w.camera(), w.input(), Iyathuum::Key::MOUSE_BUTTON_1);
      w.input().addUIElement(freeCam.get());
      fps = std::make_unique<Ahwassa::FPS>(&w);
    };

    Iyathuum::glmOctree tree(Iyathuum::glmAABB<3>(glm::vec3(0, 0, 0), 3));
    for (int i = 0; i < 2000; i++) {
      float x = (float)(rand() % 300) / 100.0f;
      float y = (float)(rand() % 300) / 100.0f;
      float z = (float)(rand() % 300) / 100.0f;
      tree.add(std::make_shared<Iyathuum::glmOctreeObject>(glm::vec3(x, y, z)));
    }

    w.Update = [&]() {

      //composer->start();
      b.draw();
      ///
      //boxRenderer->draw();
      boxRenderer->start();
      octree(boxRenderer,tree);
      boxRenderer->end();
      ///
      //composer->end();
      //
      //textureRenderer->start();
      //textureRenderer->draw(*composer->getResult(), glm::vec2(0),glm::vec2(width,height));
      //textureRenderer->end();

      fps->draw();
    };
    w.run();
  }
  Iyathuum::DatabaseTerminator::terminateAll();
}