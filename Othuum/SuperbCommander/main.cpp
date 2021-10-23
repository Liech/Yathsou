#include <iostream>
#include <filesystem>

#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Core/Camera.h"
#include "AhwassaGraphicsLib/Drawables/Background.h"
#include "AhwassaGraphicsLib/Drawables/FPS.h"
#include "AhwassaGraphicsLib/Input/FreeCamera.h"
#include "AhwassaGraphicsLib/Input/Input.h"
#include "AhwassaGraphicsLib/PostProcessing/DeferredComposer.h"
#include "AhwassaGraphicsLib/BasicRenderer/BasicTexture2DRenderer.h"
#include "AhwassaGraphicsLib/BufferObjects/VAO.h"

#include "SuthanusPhysicsLib/PhysicEngine.h"

#include "IyathuumCoreLib/Singleton/Database.h"

#include "AthanahCommonLib/Map/Map.h"
#include "AthanahCommonLib/Physic/BulletDebugDrawer.h"

#include "World.h"
#include "Config.h"
#include "Spheres.h"
#include "NavigationUI.h"
#include "PhysicsDebugView.h"

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
  
  Superb::Config config;
  config.fromJsonFile("Superb.json");
  
  int width  = config.ScreenWidth;
  int height = config.ScreenHeight;

  Ahwassa::Window                                  w(width, height);
  Ahwassa::Background                              b(&w);
  std::unique_ptr<Ahwassa::FPS>                    fps;
  std::shared_ptr<Ahwassa::FreeCamera>             freeCam;
  std::shared_ptr<Ahwassa::DeferredComposer>       composer;
  std::shared_ptr<Ahwassa::BasicTexture2DRenderer> textureRenderer;
  std::shared_ptr<Suthanus::PhysicEngine>          physic;
  std::shared_ptr<Superb::World>                   world;
  std::shared_ptr<Superb::PhysicsDebugView>        physicDebug;
  std::shared_ptr<Superb::Spheres>                 spheres;
  std::shared_ptr<Superb::NavigationUI>            navUI;

  w.Startup = [&]() {
    composer = std::make_shared<Ahwassa::DeferredComposer>(&w, width, height);
    textureRenderer = std::make_shared< Ahwassa::BasicTexture2DRenderer>(&w);
    fps = std::make_unique<Ahwassa::FPS>(&w);

    w.camera()->setPosition(config.CameraPos);
    w.camera()->setTarget  (config.CameraTarget);
    physic = std::make_shared<Suthanus::PhysicEngine>();
    physicDebug = std::make_shared<Superb::PhysicsDebugView>(physic, &w, Iyathuum::Key::KEY_F2);
    //spheres = std::make_shared<Superb::Spheres>(&w,physic);
    world = std::make_shared<Superb::World>(&w,physic, std::make_shared<Athanah::Map>(config.SupComPath + "\\" + "maps", "SCMP_009"));
    navUI = std::make_shared <Superb::NavigationUI>(&w, physic, world->navMesh());
    freeCam = std::make_shared<Ahwassa::FreeCamera>(w.camera(), w.input());

    w.input().addUIElement(freeCam.get());
    w.input().addUIElement(navUI.get());
  };
  int asd = 0;
  w.Update = [&]() {
    physic->update();
    physicDebug->update();
    world->update();
    //spheres->update();

    composer->start();
    b.draw();
    //spheres->draw();
    world->draw();
       
    
    composer->end();
    
    textureRenderer->start();
    textureRenderer->draw(*composer->getResult(), Iyathuum::glmAABB<2>(glm::vec2(0),glm::vec2(width,height)),true);
    textureRenderer->end();

    physicDebug->draw();
    world->debugDraw();
    navUI->debugDraw();

    fps->draw();
  };
  w.run();

  config.CameraPos    = w.camera()->getPosition();
  config.CameraTarget = w.camera()->getTarget  ();
  config.toJsonFile("Superb.json");

  Iyathuum::DatabaseTerminator::terminateAll();
}