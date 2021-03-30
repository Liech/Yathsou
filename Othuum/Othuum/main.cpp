#include <iostream>
#include <filesystem>

#include "YolonaOss/OpenGL/Window.h"
#include "YolonaOss/OpenGL/DrawableList.h"
#include "YolonaOss/OpenGL/DrawSpecification.h"
#include "DrawCubes.h"
#include "YolonaOss/Camera/Camera.h"
#include "YolonaOss/Camera/FreeCamera.h"
#include "YolonaOss/Camera/RTSCamera.h"
#include "YolonaOss/Camera/CameraSystem.h"
#include "YolonaOss/Drawables/Widgets/Button.h"
#include "IyathuumCoreLib/Singleton/Database.h"
#include "YolonaOss/Renderer/BoxRenderer.h"
#include "YolonaOss/Renderer/RectangleRenderer.h"
#include "YolonaOss/Examples/Texture2Tree.h"
#include "YolonaOss/Examples/RenderTexture.h"
#include <filesystem>
#include "YolonaOss/OpenGL/DrawSpecification.h"
#include <IyathuumCoreLib/lib/glm/gtx/intersect.hpp>
#include "YolonaOss/Drawables/Widgets/LineEdit.h"
#include "IyathuumCoreLib/Util/ContentLoader.h"
#include "SideProject/SideProjectMain.h"
#include "ClientControl.h"
#include <iomanip>
#include "IyathuumCoreLib/Util/UpdateTimer.h"

#include "ClientConfiguration.h"
#include "ClientState.h"
#include "MainMenuLogic.h"
#include "MainMenuLogicResult.h"
#include "UyanahGameServer/Commands/Command.h"
#include "UyanahGameServer/Commands/Key.h"
#include "UyanahGameServer/Scene.h"
#include "VishalaNetworkLib/Protocoll/AuthoritarianGameServer.h"
#include "VishalaNetworkLib/Protocoll/AuthoritarianGameClient.h"

#include "OthuumGame.h"

#include "AhwassaGraphicsLib/sound.h"

using namespace YolonaOss;

int main(int argc, char** argv) {
  {
    std::unique_ptr<OthuumGame> game = std::make_unique<OthuumGame>();
    
    std::string exe = std::string(argv[0]);
    const size_t last_slash_idx = exe.find_last_of("\\/");
    if (std::string::npos != last_slash_idx)
    {
      exe.erase(last_slash_idx + 1);
    }
    std::filesystem::current_path(exe);
    std::shared_ptr<ClientConfiguration> configuration = std::make_shared<ClientConfiguration>();
    std::shared_ptr<ClientState>         state = std::make_shared<ClientState>(configuration);
    std::string configFileName = "ClientConfiguration.json";
    configuration->fromJsonFile(configFileName);

    int width  = configuration->resolution[0];
    int height = configuration->resolution[1];
    GL::Window w(width, height);

    MainMenuLogic logic(w, configuration, state);
    std::unique_ptr<MainMenuLogicResult> rslt = nullptr;

    int tick = 0;
    auto contentCreator = [&w,&game]() {
      std::shared_ptr<Iyathuum::ContentLoader> loader = std::make_shared<Iyathuum::ContentLoader>();
      loader->addPackage([&w,&game]() {
        game->load(w.getSpec());
        }, true);
      return loader;
    };
  
    logic.setContentLoaderCreater(contentCreator);
    logic.setServerCreator([&game](int port) { game->createServer(port); });
    w.Update = [&logic, state,&rslt,&game]() {
      game->update();
      game->draw();
      if (logic.getStatus() != MainMenuLogic::status::GameRunning)
        logic.update();
      else {
        if (!rslt)
        {
          rslt = std::move(logic.extractResult());
          game->createClient(rslt->myPort, rslt->serverPort, rslt->serverIP);
        }
      }
      state->update();

    };
    w.run();

    configuration->toJsonFile(configFileName);
  }
  Iyathuum::DatabaseTerminator::terminateAll();
  std::cout << "Programm Termination" << std::endl;
} 