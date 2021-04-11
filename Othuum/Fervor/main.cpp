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
#include "AthanahCommonLib/SupComModel.h"


int main(int argc, char** argv) {
  int width = 800;
  int height = 600;
  //int width = 1920;
  //int height = 1080;

  Ahwassa::Window w(width, height);
  Ahwassa::Background b(&w);
  std::unique_ptr<Ahwassa::FPS> fps;

  std::shared_ptr<Ahwassa::FreeCamera> freeCam;
  std::shared_ptr<Athanah::SupComMeshRenderer> renderer;
  std::shared_ptr<Athanah::SupComModel> model = std::shared_ptr<Athanah::SupComModel>();
  std::vector<std::shared_ptr<Athanah::SupComMesh>> meshes;
  w.Startup = [&]() {
    renderer = std::make_shared<Athanah::SupComMeshRenderer>(w.camera());
    std::string unit = "UEL0208";
    std::string pc = "C:\\Users\\nicol\\Desktop\\units\\";
    std::string lpt = "C:\\Users\\Niki\\Desktop\\units\\";

    model = std::make_shared<Athanah::SupComModel>(lpt, unit);
    std::string animName = model->availableAnimations()[0];
    for (int x = 0; x < 50; x++) {
      int y = 0;
      //for (int y = 0; y < 50; y++) {
        std::shared_ptr<Athanah::SupComMesh> mesh = std::make_shared<Athanah::SupComMesh>();
        mesh->teamColor = Iyathuum::Color(rand()%255, rand()%255, rand()%255);
        mesh->transformation = glm::translate(glm::mat4(1.0),glm::vec3(x*10,y*10,0));
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

  w.Update = [&]() {
    b.draw();
    renderer->draw();
    fps->draw();
  };
  w.run();

  Iyathuum::DatabaseTerminator::terminateAll();
}