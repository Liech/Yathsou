#include <iostream>
#include <filesystem>

#include "IyathuumCoreLib/Singleton/Database.h"
#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Core/Camera.h"
#include "AhwassaGraphicsLib/Drawables/Background.h"
#include "AhwassaGraphicsLib/Drawables/FPS.h"
#include "AhwassaGraphicsLib/Input/Input.h"
#include "AhwassaGraphicsLib/Input/FreeCamera.h"

#include <IyathuumCoreLib/lib/glm/gtc/matrix_transform.hpp>

#include "AhwassaGraphicsLib/Util.h"
#include "AthanahCommonLib/SupComMeshLoader.h"
#include "AthanahCommonLib/SupComMeshRenderer.h"
#include "AthanahCommonLib/SupComModel.h"
#include "AezeselFileIOLib/ZIP.h"

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
  int width = 800;
  int height = 600;
  //int width = 1920;
  //int height = 1080;
  Aezesel::ZIP z;
  Ahwassa::Window w(width, height);
  Ahwassa::Background b(&w);
  std::unique_ptr<Ahwassa::FPS> fps;

  std::shared_ptr<Ahwassa::FreeCamera> freeCam;
  std::shared_ptr<Athanah::SupComMeshRenderer> renderer;
  std::shared_ptr<Athanah::SupComModel> model = std::shared_ptr<Athanah::SupComModel>();
  std::vector<std::shared_ptr<Athanah::SupComMesh>> meshes;
  std::string animName;
  w.Startup = [&]() {
    renderer = std::make_shared<Athanah::SupComMeshRenderer>(w.camera());
    std::string unit = "URL0402";//"UEL0208";
    int animationNumber = 0;
    std::string pc = "C:\\Users\\nicol\\Desktop\\units\\";
    std::string lpt = "C:\\Users\\Niki\\Desktop\\units\\";

    model = std::make_shared<Athanah::SupComModel>(pc, unit);
    animName = model->availableAnimations()[animationNumber];
    for (int x = 0; x < 2; x++) {
      std::shared_ptr<Athanah::SupComMesh> mesh = std::make_shared<Athanah::SupComMesh>();
      mesh->teamColor = Iyathuum::Color(rand()%255, rand()%255, rand()%255);
      mesh->transformation = glm::translate(glm::mat4(1.0),glm::vec3(x*100,0,0));
      mesh->model = model;
      
      mesh->animation = model->getAnimation(animName, model->getAnimationLength(animName)* x / 50.0f);
      renderer->addMesh(mesh);
      meshes.push_back(mesh);
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

    b.draw();
    renderer->draw();
    fps->draw();
  };
  w.run();

  Iyathuum::DatabaseTerminator::terminateAll();
}