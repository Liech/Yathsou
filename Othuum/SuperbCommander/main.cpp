#include <iostream>
#include <filesystem>

#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Core/Camera.h"
#include "AhwassaGraphicsLib/Input/FreeCamera.h"
#include "AhwassaGraphicsLib/Input/ArcBallCamera.h"
#include "AhwassaGraphicsLib/Input/Input.h"
#include "AhwassaGraphicsLib/PostProcessing/DeferredComposer.h"
#include "AhwassaGraphicsLib/BasicRenderer/BasicTexture2DRenderer.h"
#include "AhwassaGraphicsLib/BufferObjects/VAO.h"

#include "SuthanusPhysicsLib/PhysicEngine.h"

#include "IyathuumCoreLib/Singleton/Database.h"

#include "AthanahCommonLib/Map/Map.h"
#include "AthanahCommonLib/Physic/BulletDebugDrawer.h"
#include "AthanahCommonLib/SupCom/Gamedata/Gamedata.h"

#include "World.h"
#include "Config.h"
#include "Spheres.h"
#include "Units.h"
#include "NavigationUI.h"
#include "PhysicsDebugView.h"
#include "UnitsVisualization.h"
#include "DriveInterface.h"
#include "Game/Game.h"
#include "Game/Physic.h"
#include "Game/Database.h"

#include "AthanahCommonLib/SupCom/Gamedata/BlueprintFactory.h"

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
  std::shared_ptr<Ahwassa::FreeCamera>             freeCam;
  std::shared_ptr<Ahwassa::ArcBallCamera>          arcCam;
  std::shared_ptr<Ahwassa::DeferredComposer>       composer;
  std::shared_ptr<Ahwassa::BasicTexture2DRenderer> textureRenderer;
  std::shared_ptr<Superb::World>                   world;
  std::shared_ptr<Superb::Units>                   units;
  std::shared_ptr<Superb::UnitsVisualization>      unitsVis;

  std::shared_ptr<Superb::PhysicsDebugView>        physicDebug;
  std::shared_ptr<Superb::Spheres>                 spheres;
  std::shared_ptr<Superb::NavigationUI>            navUI;
  std::shared_ptr<Superb::DriveInterface>          driveUI;

  std::unique_ptr<Superb::Game>                    game;

  w.Startup = [&]() {
    game = std::make_unique<Superb::Game>(w);
    composer = std::make_shared<Ahwassa::DeferredComposer>(&w, width, height);
    textureRenderer = std::make_shared< Ahwassa::BasicTexture2DRenderer>(&w);

    w.camera()->setPosition(config.CameraPos);
    w.camera()->setTarget  (config.CameraTarget);
    physicDebug = std::make_shared<Superb::PhysicsDebugView>(game->physic().physic(), &w, Iyathuum::Key::KEY_F2);
    //spheres = std::make_shared<Superb::Spheres>(&w,physic);
    world = std::make_shared<Superb::World>(&w, game->physic().physic(), std::make_shared<Athanah::Map>(config.SupComPath + "\\" + "maps", "SCMP_009"), game->database().gamedata());
    units = std::make_shared<Superb::Units>(game->database().gamedata(),&w, game->physic().physic());
    unitsVis = std::make_shared<Superb::UnitsVisualization>(&w, game->database().gamedata(),*units);
    navUI = std::make_shared <Superb::NavigationUI>(&w, game->physic().physic(), world->navMesh(), units);
    freeCam = std::make_shared<Ahwassa::FreeCamera   >(w.camera(), w.input(), Iyathuum::Key::KEY_F3);
    arcCam = std::make_shared<Ahwassa::ArcBallCamera>(w.camera(), w.input(), Iyathuum::Key::KEY_F4);
    driveUI = std::make_shared<Superb::DriveInterface>(w.input());

    w.input().addUIElement(freeCam.get());
    w.input().addUIElement(arcCam .get());
    w.input().addUIElement(navUI.get());
  };
  int asd = 0;
  bool pressed = false;
  bool debugOn = true;
  w.Update = [&]() {
    game->update();
    physicDebug->update();
    world->update();
    units->update();
    driveUI->update();
    //spheres->update();
    //asd=(asd+1)%20;
    //if (asd == 0) spheres->addSphere(w.camera()->getPosition(),0.5f,Iyathuum::Color(255,0,0));

    if (arcCam->isFocus() && navUI->selection().size() > 0) {
      w.camera()->setTarget(navUI->selection()[0]->getPosition());
      driveUI->setTarget(navUI->selection()[0]->getPhysic());
    }
    else
      driveUI->setTarget(nullptr);

    if (!pressed && w.input().getKeyStatus(Iyathuum::Key::KEY_F5) == Iyathuum::KeyStatus::PRESS) {
      pressed = true;
      debugOn = !debugOn;
    }
    else if (w.input().getKeyStatus(Iyathuum::Key::KEY_F5) == Iyathuum::KeyStatus::RELEASE)
      pressed = false;

    composer->start();

    game->drawFirstLayer();
    //spheres->draw();
    world->draw();
    unitsVis->draw();
       
    
    composer->end();
    
    textureRenderer->start();
    textureRenderer->draw(*composer->getResult(), Iyathuum::glmAABB<2>(glm::vec2(0),glm::vec2(width,height)),true);
    textureRenderer->end();
    
    composer->blitDepth();

    physicDebug->draw();

    if (debugOn) {
      world->debugDraw();
      navUI->debugDraw();
      unitsVis->debugDraw();
    }

    game->drawLastLayer();
    game->drawMenu();
  };
  w.run();

  config.CameraPos    = w.camera()->getPosition();
  config.CameraTarget = w.camera()->getTarget  ();
  config.toJsonFile("Superb.json");

  Iyathuum::DatabaseTerminator::terminateAll();
}