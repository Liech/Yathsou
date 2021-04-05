#include <iostream>
#include <filesystem>
#include <iomanip>

#include "IyathuumCoreLib/Singleton/Database.h"
#include <IyathuumCoreLib/lib/glm/gtx/intersect.hpp>
#include "IyathuumCoreLib/Util/UpdateTimer.h"

#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Widgets/Button.h"
#include "AhwassaGraphicsLib/Widgets/LineEdit.h"
#include "IyathuumCoreLib/Util/ContentLoader.h"
#include "SideProject/SideProjectMain.h"
#include "ClientControl.h"
#include "DrawCubes.h"

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


int main(int argc, char** argv) {
  {
    
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
    Ahwassa::Window w(width, height);
    std::unique_ptr<OthuumGame> game = std::make_unique<OthuumGame>(&w,false);

    MainMenuLogic logic(&w, configuration, state);
    std::unique_ptr<MainMenuLogicResult> rslt = nullptr;

    int tick = 0;
    auto contentCreator = [&w,&game]() {
      std::shared_ptr<Iyathuum::ContentLoader> loader = std::make_shared<Iyathuum::ContentLoader>();
      loader->addPackage([&w,&game]() {
//        game->load(w.getSpec());
        throw std::runtime_error("Not yet implemented");
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