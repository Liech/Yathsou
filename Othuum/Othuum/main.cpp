#include <iostream>
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

#include "MainMenuPage.h"
#include "JoinLobbyPage.h"

using namespace YolonaOss;

int main() { 
  {
    int width = 1420;
    int height = 880;
    GL::Window w(width, height);
    
    enum class status { MainMenu, LobbyEntry } stat= status::MainMenu;

    std::shared_ptr<MainMenuPage > mainMenu   = std::make_shared<MainMenuPage >();
    std::shared_ptr<JoinLobbyPage> lobbyEntry = std::make_shared<JoinLobbyPage>();

    Iyathuum::Database<std::shared_ptr<GL::Drawable>>::add(mainMenu  , { "Main" });
    Iyathuum::Database<std::shared_ptr<GL::Drawable>>::add(lobbyEntry, { "Main" });

    w.Update = [mainMenu, lobbyEntry,&stat]() {
      if (mainMenu->getStatus() == MainMenuPageStatus::Multiplayer && stat == status::MainMenu) {
        mainMenu->reset();
        mainMenu  ->setVisible(false);
        lobbyEntry->setVisible(true);
        stat = status::LobbyEntry;
      }
      else if (lobbyEntry->getStatus() == JoinLobbyPageStatus::Back && stat == status::LobbyEntry) {
        mainMenu  ->setVisible(true);
        lobbyEntry->setVisible(false);
        stat = status::MainMenu;
        lobbyEntry->reset();
      }
    };
    w.run();
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