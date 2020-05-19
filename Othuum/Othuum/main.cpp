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

#include "DialogPage.h"

using namespace YolonaOss;

int main() { 
  {
    int width = 1420;
    int height = 880;
    GL::Window w(width, height);

    std::shared_ptr<DialogPage> mainMenu = std::make_shared<DialogPage>(1420,880);
    Iyathuum::Database<std::shared_ptr<GL::Drawable>>::add(mainMenu, { "Main" });

    mainMenu->addButton("HUHU", []() {std::cout << "HUHU" << std::endl; });
    mainMenu->addButton("HUHU", []() {std::cout << "HUHU" << std::endl; });
    mainMenu->addButton("HUHU", []() {std::cout << "HUHU" << std::endl; });


    std::shared_ptr<YolonaOss::Widgets::LineEdit> lineEdit = std::make_shared<YolonaOss::Widgets::LineEdit>("Kartoffel", Iyathuum::AABB<2>({0,0}, {200,100}));
    Iyathuum::Database<std::shared_ptr<GL::Drawable>>::add(lineEdit, { "Main" });

    w.Update = [&w, width, height]() {

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