#include <iostream>

#include "IyathuumCoreLib/Singleton/Database.h"
#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Core/Camera.h"
#include "AhwassaGraphicsLib/Drawables/Background.h"
#include "AhwassaGraphicsLib/Drawables/FPS.h"
#include "AhwassaGraphicsLib/Input/Input.h"
#include "AhwassaGraphicsLib/Input/FreeCamera.h"

#include <IyathuumCoreLib/lib/glm/gtc/matrix_transform.hpp>

//#include "AhwassaGraphicsLib/Renderer/DiffuseMeshRenderer.h"
#include "AhwassaGraphicsLib/Util.h"
#include "AthanahCommonLib/SupComMeshLoader.h"
#include "AthanahCommonLib/SupComMeshRenderer.h"
#include "AhwassaGraphicsLib/Renderer/BoxRenderer.h"
#include "AhwassaGraphicsLib/Renderer/Box.h"
#include "AthanahCommonLib/SupComModel.h"

int main(int argc, char** argv) {
  //int width = 800;
  //int height = 600;
  int width = 1920;
  int height = 1080;

  Ahwassa::Window w(width, height);
  Ahwassa::Background b(&w);
  std::unique_ptr<Ahwassa::FPS> fps;

  std::shared_ptr<Ahwassa::FreeCamera> freeCam;
  std::shared_ptr<Athanah::SupComMeshRenderer> renderer;
  std::shared_ptr<Ahwassa::BoxRenderer> boxr;
  std::vector<std::shared_ptr<Ahwassa::Box>> boxes;
  std::shared_ptr<Athanah::SupComModel> model = std::shared_ptr<Athanah::SupComModel>();
  std::vector<std::shared_ptr<Athanah::SupComMesh>> meshes;
  std::string animName;
  w.Startup = [&]() {
    renderer = std::make_shared<Athanah::SupComMeshRenderer>(w.camera());
    boxr = std::make_shared<Ahwassa::BoxRenderer>(w.camera());
    std::string unit = "UAL0401";//"UEL0208";
    int animationNumber = 4;
    std::string pc = "C:\\Users\\nicol\\Desktop\\units\\";
    std::string lpt = "C:\\Users\\Niki\\Desktop\\units\\";

    for (int i = 0; i < 10; i++) {
      boxes.push_back(boxr->newBox(glm::mat4()));      
    }

    model = std::make_shared<Athanah::SupComModel>(pc, unit);
    animName = model->availableAnimations()[animationNumber];
    for (int x = 0; x < 2; x++) {
      int y = 0;
      //for (int y = 0; y < 50; y++) {
        std::shared_ptr<Athanah::SupComMesh> mesh = std::make_shared<Athanah::SupComMesh>();
        mesh->teamColor = Iyathuum::Color(rand()%255, rand()%255, rand()%255);
        mesh->transformation = glm::translate(glm::mat4(1.0),glm::vec3(x*100,y*100,0));
        mesh->model = model;
        
        mesh->animation = model->getAnimation(animName, model->getAnimationLength(animName)* x / 50.0f);
        //mesh->animation.push_back(glm::rotate(glm::mat4(1.0), glm::pi<float>() * x / 50.0f, glm::vec3(0, 1, 0)));
        renderer->addMesh(mesh);
        meshes.push_back(mesh);
      //}
    }

    freeCam = std::make_shared<Ahwassa::FreeCamera>(w.camera(), w.input());
    w.input().addUIElement(freeCam.get());
    fps = std::make_unique<Ahwassa::FPS>(&w);
  };

  float t = 0;
  w.Update = [&]() {
    t += 0.01f;
    meshes[0]->animation = model->getAnimation(animName, model->getAnimationLength(animName) * std::fmod(t, 1));
    meshes[1]->animation = {};


    for (int i = 0; i < 10; i++) {
      glm::mat4 argh = glm::mat4(1);
      argh = glm::translate(argh, glm::vec3(5 * i, 5, 5));
      argh = glm::scale(argh, glm::vec3(1,2,1));
      boxes[i]->setMatrix(argh*meshes[0]->animation[i]);
    }

    b.draw();
    renderer->draw();
    boxr->draw();
    fps->draw();
  };
  w.run();

  Iyathuum::DatabaseTerminator::terminateAll();
}