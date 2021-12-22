#include <iostream>
#include <filesystem>

#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Core/Camera.h"
#include "AhwassaGraphicsLib/Input/Input.h"
#include "AhwassaGraphicsLib/BasicRenderer/BasicTexture2DRenderer.h"
#include "AhwassaGraphicsLib/BufferObjects/VAO.h"
#include "AhwassaGraphicsLib/Input/ArcBallCamera.h"

#include "SuthanusPhysicsLib/PhysicEngine.h"

#include "IyathuumCoreLib/Singleton/Database.h"

#include "AthanahCommonLib/Map/Map.h"
#include "AthanahCommonLib/Physic/BulletDebugDrawer.h"
#include "AthanahCommonLib/SupCom/Gamedata/Gamedata.h"

#include "World.h"
#include "Config.h"
#include "Spheres.h"
#include "UnitsOld.h"

#include "Game/Game.h"
#include "Game/Physic.h"
#include "Game/Database.h"
#include "Game/Terrain.h"
#include "Game/Units.h"
#include "Game/Control.h"

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

  Ahwassa::Window w(width, height);

  std::unique_ptr<Superb::Game> game;

  w.Startup = [&]() {
    game = std::make_unique<Superb::Game>(w);

    w.camera()->setPosition(config.CameraPos);
    w.camera()->setTarget  (config.CameraTarget);
  };
  w.Update = [&]() {
    game->update();
    game->draw();
    game->drawMenu();
  };
  w.run();

  config.CameraPos    = w.camera()->getPosition();
  config.CameraTarget = w.camera()->getTarget  ();
  config.toJsonFile("Superb.json");

  Iyathuum::DatabaseTerminator::terminateAll();
}