#include <iostream>
#include <filesystem>

#include "YolonaOss/OpenGL/Window.h"
#include "YolonaOss/OpenGL/DrawableList.h"
#include "YolonaOss/OpenGL/DrawSpecification.h"
#include "YolonaOss/Drawables/Background.h"
#include "DrawCubes.h"
#include "YolonaOss/Camera/Camera.h"
#include "YolonaOss/Camera/FreeCamera.h"
#include "YolonaOss/Camera/RTSCamera.h"
#include "YolonaOss/Camera/CameraSystem.h"
#include "YolonaOss/Drawables/FPS.h"
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
#include "ClientVisualization/ClientVisualization.h"
#include "ClientControl.h"
#include <iomanip>
#include "IyathuumCoreLib/Util/UpdateTimer.h"

#include "ClientConfiguration.h"
#include "ClientState.h"
#include "MainMenuLogic.h"
#include "MainMenuLogicResult.h"
#include "UyanahGameServer/Commands/Command.h"
#include "UyanahGameServer/Commands/Key.h"
#include "UyanahGameServer/Commands/UpdateScene.h"
#include "UyanahGameServer/Scene.h"
#include "VishalaNetworkLib/Protocoll/AuthoritarianGameServer.h"
#include "VishalaNetworkLib/Protocoll/AuthoritarianGameClient.h"

#include "UyanahGameServer/Components/Dot.h"
#include "UyanahGameServer/Components/Transform2D.h"

#include "AhwassaGraphicsLib/sound.h"

using namespace YolonaOss;

int main(int argc, char** argv) {
  {
    //Ahwassa::sound s;
    //s.play();
    std::unique_ptr<Vishala::AuthoritarianGameClient<Uyanah::Scene>> client = nullptr;
    std::shared_ptr<Uyanah::Scene> s = std::make_shared<Uyanah::Scene>();



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

    std::shared_ptr<ClientControl> control = nullptr;
    glm::vec2 v;
    int tick = 0;
    Iyathuum::UpdateTimer timer([&control, &tick,&v,&rslt,&client,&s]() {
      control->update();
      if (client)
        client->update();
      v = glm::vec2(200, 200) + glm::vec2(std::cos(tick / 10.0f) * 50, std::sin(tick / 10.0f) * 50);
      tick++;
    }, 30);
    std::shared_ptr<ClientVisualization> vis = nullptr;
    auto contentCreator = [&w,&vis,&rslt,&control,&timer,&client,&s]() {
      std::shared_ptr<Iyathuum::ContentLoader> loader = std::make_shared<Iyathuum::ContentLoader>();
      loader->addPackage([&w,&vis,&rslt,&control,&timer,&client,&s]() {
        vis = std::make_shared<ClientVisualization>(s);
        std::shared_ptr<GL::DrawableList> list = std::make_shared<GL::DrawableList>();
        list->addDrawable(std::make_shared<Background>());
        list->addDrawable(std::make_shared<FPS>());
        list->addDrawable(vis);
        list->load(w.getSpec());
        Iyathuum::Database<std::shared_ptr<GL::Drawable>>::add(list, { "Main" });
        auto s = std::make_shared<Uyanah::Scene>();
        timer.setTicksPerSecond(30);
        control = std::make_shared<ClientControl>(
          [&rslt,&client](std::shared_ptr<Vishala::ICommand> cmd) {
          client->sendCmd(*cmd);
          },
          s
          );
        control->load(w.getSpec());
        }, true);
      return loader;
    };
  
    std::unique_ptr<Vishala::AuthoritarianGameServer> server;
    logic.setContentLoaderCreater(contentCreator);
    logic.setServerCreator([&server](int port) {
      std::unique_ptr<Uyanah::Scene> scene = std::make_unique<Uyanah::Scene>();

      Uyanah::Entity a;
      std::shared_ptr<Uyanah::Components::Transform2D> aTransform = std::make_shared<Uyanah::Components::Transform2D>();
      aTransform->position = glm::vec2(5, 5);
      std::shared_ptr<Uyanah::Components::Dot> aDot = std::make_shared<Uyanah::Components::Dot>();
      a.addComponent(aTransform);
      a.addComponent(aDot);

      for (int i = 0; i < 600; i++) {
        Uyanah::Entity b;
        std::shared_ptr<Uyanah::Components::Transform2D> bTransform = std::make_shared<Uyanah::Components::Transform2D>();
        bTransform->position = glm::vec2(rand() % 300, rand() % 300);
        std::shared_ptr<Uyanah::Components::Dot> bDot = std::make_shared<Uyanah::Components::Dot>();
        b.addComponent(bTransform);
        b.addComponent(bDot);
        scene->objects.push_back(b);
      }
      scene->objects.push_back(a);

      server = std::make_unique<Vishala::AuthoritarianGameServer>(std::move(scene),port,30);
      server->addOnUpdate(std::make_unique<Uyanah::Commands::UpdateScene>());
    });
    w.Update = [&logic, state,&rslt,&vis,&timer,&control,&v,&s,&client,&server]() {
      if (server)
        server->update();
      if (logic.getStatus() != MainMenuLogic::status::GameRunning)
        logic.update();
      else {
        if (!rslt)
        {
          rslt = std::move(logic.extractResult());
          
          client = std::make_unique<Vishala::AuthoritarianGameClient<Uyanah::Scene>>(s,30,rslt->myPort,rslt->serverPort,rslt->serverIP);
        }
      }
      state->update();

      if (control)
        timer.update();
    };
    w.run();

    configuration->toJsonFile(configFileName);
  }
  Iyathuum::DatabaseTerminator::terminateAll();
  std::cout << "Programm Termination" << std::endl;
} 

/*
std::shared_ptr<GL::DrawableList> list = std::make_shared<GL::DrawableList>();
    list->addDrawable(std::make_shared<Background>());
    list->addDrawable(std::make_shared<FPS>());
    Iyathuum::Database<std::shared_ptr<GL::Drawable>>::add(list, { "Main" });
    std::shared_ptr<Camera::CameraSystem> cam = std::make_shared<Camera::CameraSystem>();

    list->addDrawable(std::make_shared<Texture2Tree>());
    std::shared_ptr<Widgets::Button> b = std::make_shared<Widgets::Button>("FreeCam", Iyathuum::AABB<2>({ 0.0, 0.0 }, { 200.0, 50.0 }), [cam]() {cam->setCurrentCam("FreeCamera"); });
    list->addDrawable(b);

    Iyathuum::Database<std::shared_ptr<GL::Updateable>>::add(cam, { "Main" });
    glm::vec3 start, end;

*/