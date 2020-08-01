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
#include "YolonaOss/Examples/Texture2Tree.h"
#include "YolonaOss/Examples/RenderTexture.h"
#include <filesystem>
#include "YolonaOss/OpenGL/DrawSpecification.h"
#include <glm/gtx/intersect.hpp>
#include "YolonaOss/Drawables/Widgets/LineEdit.h"
#include <iomanip>

#include "ClientConfiguration.h"
#include "ClientState.h"
#include "MainMenuLogic.h"

#include "AhwassaGraphicsLib/sound.h"

using namespace YolonaOss;

int main(int argc, char** argv) {
  {
    Ahwassa::sound s;
    s.play();

    std::string exe = std::string(argv[0]);
    const size_t last_slash_idx = exe.find_last_of("\\/");
    if (std::string::npos != last_slash_idx)
    {
      exe.erase(last_slash_idx + 1);
    }


    std::filesystem::current_path(exe);
    std::shared_ptr<ClientConfiguration> configuration = std::make_shared<ClientConfiguration>();
    std::shared_ptr<ClientState>         state         = std::make_shared<ClientState>(configuration);
    std::string configFileName = "ClientConfiguration.json";
    configuration->fromJsonFile(configFileName);

    int width  = configuration->resolution[0];
    int height = configuration->resolution[1];
    GL::Window w(width, height);
    
    MainMenuLogic logic(w,configuration,state);

    w.Update = [&logic, state]() {
      logic.update();
      state->update();
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