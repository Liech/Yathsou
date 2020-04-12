#include <iostream>
#include "YolonaOss/OpenGL/Window.h"
#include "YolonaOss/OpenGL/DrawableList.h"
#include "YolonaOss/OpenGL/DrawSpecification.h"
#include "YolonaOss/Drawables/Background.h"
#include "DrawCubes.h"
#include "YolonaOss/Camera/FreeCamera.h"
#include "YolonaOss/Camera/RTSCamera.h"
#include "YolonaOss/Camera/CameraSystem.h"
#include "YolonaOss/Drawables/FPS.h"
#include "YolonaOss/Drawables/Widgets/Button.h"
#include "YolonaOss/structs/Database.h"
#include "YolonaOss/Renderer/BoxRenderer.h"
#include "YolonaOss/Examples/Texture2Tree.h"
#include "YolonaOss/Examples/RenderTexture.h"
#include <filesystem>
#include "YolonaOss/OpenGL/DrawSpecification.h"
#include <glm/gtx/intersect.hpp>
#include <iomanip>
using namespace YolonaOss;

int main() { 
  {

    //int width = 800;
    //int height = 600;
    int width = 1420;
    int height = 880;
    GL::Window w(width, height);


    std::shared_ptr<GL::DrawableList> list = std::make_shared<GL::DrawableList>();
    list->addDrawable(std::make_shared<Background>());
    //list->addDrawable(std::make_shared<DrawCubes>()); 
    //list->addDrawable(std::make_shared<RenderTexture>());
    list->addDrawable(std::make_shared<FPS>());
    Database<std::shared_ptr<GL::Drawable>>::add(list, { "Main" });
    std::shared_ptr<Camera::CameraSystem> cam = std::make_shared<Camera::CameraSystem>();

    list->addDrawable(std::make_shared<Texture2Tree>());
    std::shared_ptr<Widgets::Button> b = std::make_shared<Widgets::Button>("FreeCam", BoundingBox2(glm::vec2(0, 0), glm::vec2(200, 50)), [cam]() {cam->setCurrentCam("FreeCamera"); });
    list->addDrawable(b);


    Database<std::shared_ptr<GL::Updateable>>::add(cam, { "Main" });
    glm::vec3 start, end;

    w.Update = [&w, &start, &end, width, height]() {
      //f(0, 0);
      glm::vec3 viewDir = glm::normalize(w.getSpec()->getCam()->getTarget() - w.getSpec()->getCam()->getPosition());
      glm::vec3 dir = w.getSpec()->getCam()->getPickRay((float)w.getCursorPos().first, w.getCursorPos().second);
      glm::vec3 pos = w.getSpec()->getCam()->getPosition();
      //std::cout << "center: " << viewDir[0] << "/" << viewDir[1] << "/" << viewDir[2] << "   " << dir[0] << "/" << dir[1] << "/" << dir[2] << std::endl<<std::setprecision(2) << std::setfill('0');
      //std::cout << "view  : " <<  << std::endl<<std::setprecision(2) << std::setfill('0');;
      //w.getSpec()->getCam()->getPickRay(&w, w.getCursorPos().first, w.getCursorPos().second);
      //BoxRenderer::start();
      //BoxRenderer::drawDot(glm::vec3(0), glm::vec3(0.01f, 0.01f, 0.01f), glm::vec4(0.9, 1, 1, 1));
      //BoxRenderer::drawDot(pos + dir, glm::vec3(0.05f, 0.05f, 0.05f), glm::vec4(0.9, 1, 0, 1));
      //BoxRenderer::drawDot(pos + w.getSpec()->getCam()->getPickRay(0, 0)          , glm::vec3(0.05f, 0.05f, 0.05f), glm::vec4(0.9, 1, 0, 1));
      //BoxRenderer::drawDot(pos + w.getSpec()->getCam()->getPickRay(width, 0)       , glm::vec3(0.05f, 0.05f, 0.05f), glm::vec4(0.9, 1, 0, 1));
      //BoxRenderer::drawDot(pos + w.getSpec()->getCam()->getPickRay(0, height)       , glm::vec3(0.05f, 0.05f, 0.05f), glm::vec4(0.9, 1, 0, 1));
      //BoxRenderer::drawDot(pos + w.getSpec()->getCam()->getPickRay(width, height)    , glm::vec3(0.05f, 0.05f, 0.05f), glm::vec4(0.9, 1, 0, 1));
      //BoxRenderer::drawDot(pos + w.getSpec()->getCam()->getPickRay(width/2, height/2), glm::vec3(0.05f, 0.05f, 0.05f), glm::vec4(0.9, 1, 0, 1));
      //BoxRenderer::end();
    };
    w.run();
  }
  DatabaseTerminator::terminateAll();
  std::cout << "Programm Termination" << std::endl;
} 