#include <iostream>
#include <filesystem>

#include "IyathuumCoreLib/Singleton/Database.h"
#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Core/Camera.h"
#include "AhwassaGraphicsLib/PostProcessing/DeferredComposer.h"
#include "AhwassaGraphicsLib/Drawables/Background.h"
#include "AhwassaGraphicsLib/Drawables/FPS.h"
#include "AhwassaGraphicsLib/Input/Input.h"
#include "AhwassaGraphicsLib/Input/FreeCamera.h"
#include "AhwassaGraphicsLib/Input/FileDropper.h"
#include "AhwassaGraphicsLib/BasicRenderer/BasicTexture2DRenderer.h"
#include "AhwassaGraphicsLib/BufferObjects/FBO.h"

#include <IyathuumCoreLib/lib/glm/gtc/matrix_transform.hpp>

#include "AhwassaGraphicsLib/Util.h"
#include "AthanahCommonLib/Model3DRenderer.h"
#include "AezeselFileIOLib/Model3D.h"

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
  std::shared_ptr<Athanah::Model3DRendererMesh> mesh;
  Ahwassa::Window w(width, height);
  
  {  //better context for window
    Ahwassa::Background b(&w);
    std::unique_ptr<Ahwassa::FPS> fps;

    std::shared_ptr<Ahwassa::FreeCamera> freeCam;
    std::shared_ptr<Ahwassa::FileDropper> dropper;
    std::shared_ptr<Ahwassa::DeferredComposer> composer;
    std::shared_ptr<Ahwassa::BasicTexture2DRenderer> textureRenderer;
    std::shared_ptr<Athanah::Model3DRenderer> renderer;
    std::shared_ptr<Ahwassa::IMesh> m;

    w.Startup = [&]() {
      composer = std::make_shared<Ahwassa::DeferredComposer>(&w, width, height);
      textureRenderer = std::make_shared< Ahwassa::BasicTexture2DRenderer>(&w);
      renderer = std::make_shared<Athanah::Model3DRenderer>(w.camera());
      renderer->init();

      
      mesh = std::make_shared<Athanah::Model3DRendererMesh>();
      mesh->transformation = glm::mat4(1);
      Aezesel::Model3D modl("C:\\Users\\nicol\\Seafile\\Sea\\Code\\Soon\\MainProject\\Data\\Modells\\Clonk\\Graphics.mesh.xml");
      m = renderer->meshFromModel3D(modl);
      renderer->addInstance(m, mesh);

      dropper = std::make_shared<Ahwassa::FileDropper>([&](const std::string& path) {
        renderer->clear();
        Aezesel::Model3D mdl(path);
        m = renderer->meshFromModel3D(mdl);
        renderer->addInstance(m, mesh);
      });
      dropper->setLocalPosition(Iyathuum::glmAABB<2>(glm::vec2(0, 0), w.camera()->getResolution()));
      w.input().addUIElement(dropper.get());

      freeCam = std::make_shared<Ahwassa::FreeCamera>(w.camera(), w.input());
      w.input().addUIElement(freeCam.get());
      fps = std::make_unique<Ahwassa::FPS>(&w);
    };

    w.Update = [&]() {

      composer->start();
      renderer->draw();
      composer->end();

      textureRenderer->start();
      auto loc = Iyathuum::glmAABB<2>(glm::vec2(0, 0), glm::vec2(w.getWidth() / 3, w.getHeight() / 3));
      auto loc2 = Iyathuum::glmAABB<2>(glm::vec2(w.getWidth() / 3, 0), glm::vec2(w.getWidth() / 3, w.getHeight() / 3));
      auto loc3 = Iyathuum::glmAABB<2>(glm::vec2(0, w.getHeight() / 3), glm::vec2(w.getWidth() / 3, w.getHeight() / 3));
      auto loc4 = Iyathuum::glmAABB<2>(glm::vec2(w.getWidth() / 3, w.getHeight() / 3), glm::vec2(w.getWidth() / 3, w.getHeight() / 3));
      auto loc5 = Iyathuum::glmAABB<2>(glm::vec2(2 * w.getWidth() / 3, w.getHeight() / 3), glm::vec2(w.getWidth() / 3, w.getHeight() / 3));
      auto loc6 = Iyathuum::glmAABB<2>(glm::vec2(2 * w.getWidth() / 3, 0), glm::vec2(w.getWidth() / 3, w.getHeight() / 3));
      auto loc7 = Iyathuum::glmAABB<2>(glm::vec2(0, 2 * w.getHeight() / 3), glm::vec2(w.getWidth() / 3, w.getHeight() / 3));
      textureRenderer->draw(*composer->getRawTextures()[0], loc, true);
      textureRenderer->draw(*composer->getRawTextures()[1], loc2, true);
      textureRenderer->draw(*composer->getRawTextures()[2], loc3, true);
      textureRenderer->draw(*composer->getRawTextures()[3], loc4, true);
      textureRenderer->draw(*composer->getResult(), loc5, true);
      textureRenderer->draw(*composer->getDepth(), loc7, true);
      textureRenderer->end();

      fps->draw();
    };
    w.run();
  }
  Iyathuum::DatabaseTerminator::terminateAll();
}