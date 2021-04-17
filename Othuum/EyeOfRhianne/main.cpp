#include <iostream>
#include <filesystem>

#include "IyathuumCoreLib/Singleton/Database.h"

#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Core/Camera.h"
#include "AhwassaGraphicsLib/Drawables/Background.h"
#include "AhwassaGraphicsLib/Drawables/FPS.h"
#include "AhwassaGraphicsLib/Widgets/Button.h"
#include "AhwassaGraphicsLib/Input/Input.h"
#include "AhwassaGraphicsLib/Input/FreeCamera.h"

#include "AthanahCommonLib/SupComModelFactory.h"
#include "AthanahCommonLib/SupComModel.h"
#include "AthanahCommonLib/SupComMeshRenderer.h"

#include "AezeselFileIOLib/STLWriter.h"
#include "AezeselFileIOLib/SupremeCommander/SCM.h"

#include "ListSelection.h"
#include "AthanahCommonLib/BlueprintFactory.h"
#include "AthanahCommonLib/Blueprint.h"

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
  int width = 1200;
  int height = 900;
  //int width = 1920;
  //int height = 1080;

  //std::string pc = "C:\\Users\\nicol\\Desktop\\units\\";
  //std::string lpt = "C:\\Users\\Niki\\Desktop\\units\\";
  
  Ahwassa::Window w(width, height);
  std::unique_ptr<Ahwassa::Background> background;
  std::unique_ptr<Ahwassa::FPS       > fps;
  std::unique_ptr<ListSelection      > UnitSelection;
  std::unique_ptr<ListSelection      > AnimationSelection = nullptr;
  std::unique_ptr<Ahwassa::Button    > PauseButton;
  std::unique_ptr<Ahwassa::Button    > SaveButton = nullptr;
  Athanah::SupComModelFactory factory("Data\\units\\");
  std::shared_ptr<Athanah::SupComMesh> mesh;
  std::unique_ptr<Athanah::SupComMeshRenderer> renderer;
  bool play = true;
  float time = 0;
  
  std::string currentAnimation = "None";

  Athanah::BlueprintFactory blueprints("Data\\units\\");

  std::shared_ptr<Ahwassa::FreeCamera> freeCam;
  Iyathuum::glmAABB<2> animListArea;
  Iyathuum::glmAABB<2> pauseArea;
  Iyathuum::glmAABB<2> saveArea;
  w.Startup = [&]() {
    Iyathuum::glmAABB<2> unitListArea(glm::vec2(0, 0), glm::vec2(300, w.getHeight()));
    animListArea = Iyathuum::glmAABB<2>(glm::vec2(300, 0), glm::vec2(300, w.getHeight() / 4));
    saveArea    = Iyathuum::glmAABB<2>(glm::vec2(300, w.getHeight() -50), glm::vec2(150, 50));
    pauseArea    = Iyathuum::glmAABB<2>(glm::vec2(450, w.getHeight() -50), glm::vec2(150, 50));

    freeCam = std::make_shared<Ahwassa::FreeCamera>(w.camera(), w.input());
    w.camera()->setPosition(glm::vec3(20, 20, 20));
    w.input().addUIElement(freeCam.get());

    std::vector<std::string> names;
    
    for (auto x : factory.getAvailableModels()) {
      auto bp = blueprints.loadModel(x);
      names.push_back(bp->getName());
    }

    UnitSelection = std::make_unique<ListSelection>(factory.getAvailableModels(),names, unitListArea, &w, [&](std::string u) {
      mesh = std::make_shared<Athanah::SupComMesh>();
      mesh->model = factory.loadModel(u);
      mesh->teamColor = Iyathuum::Color(rand() % 255, rand() % 255, rand() % 255);
      mesh->transformation = glm::translate(glm::mat4(1.0), glm::vec3(0, 0, 0));
      renderer->addMesh(mesh);

      SaveButton = std::make_unique<Ahwassa::Button>("Save", saveArea, [&]() { 
        std::vector<glm::vec3> data;
        data.resize(mesh->model->scm().indices.size()*3);
        for (size_t i = 0; i < mesh->model->scm().indices.size(); i++) {
          auto v1 = mesh->model->scm().vertecies[mesh->model->scm().indices[i].a];
          auto v2 = mesh->model->scm().vertecies[mesh->model->scm().indices[i].b];
          auto v3 = mesh->model->scm().vertecies[mesh->model->scm().indices[i].c];
          auto mat1 = glm::mat4(1.0);
          auto mat2 = glm::mat4(1.0);
          auto mat3 = glm::mat4(1.0);

          if (currentAnimation != "None") {
            mat1 = mesh->animation[v1.boneIndex[0]];
            mat2 = mesh->animation[v2.boneIndex[0]];
            mat3 = mesh->animation[v3.boneIndex[0]];
          }

          data[i * 3 + 0] = mat1*glm::vec4(v1.position,1);
          data[i * 3 + 1] = mat2*glm::vec4(v2.position,1);
          data[i * 3 + 2] = mat3*glm::vec4(v3.position,1);
        }
        Aezesel::STLWriter::write("Output.stl", data);
      }, &w);

      currentAnimation = "None";
      std::vector<std::string> available = mesh->model->availableAnimations();
      std::vector<std::string> anims;
      anims.push_back("None");
      anims.insert(anims.begin(), available.begin(), available.end());
      if (anims.size() > 1) {
        AnimationSelection = std::make_unique<ListSelection>(anims, anims, animListArea, &w, [&](std::string u) {
          currentAnimation = u;
          time = 0;
        });
        PauseButton = std::make_unique<Ahwassa::Button>("Pause", pauseArea, [&]() {
          play = !play; 
          if (play)
            PauseButton->setText("Pause");
          else
            PauseButton->setText("Play");
        }, &w);
      }
      else {
        AnimationSelection = nullptr;
        PauseButton = nullptr;
      }

    });

    fps = std::make_unique<Ahwassa::FPS>(&w);
    background = std::make_unique<Ahwassa::Background>(&w);

    renderer = std::make_unique<Athanah::SupComMeshRenderer>(w.camera());
  };

  w.Update = [&]() {
    if (play)
      time = std::fmod(time+0.01f,1);
    
    if (mesh) {
      if (currentAnimation != "None")
        mesh->animation = mesh->model->getAnimation(currentAnimation, mesh->model->getAnimationLength(currentAnimation) * time);
      else
        mesh->animation = std::vector<glm::mat4>();
    }

    background->draw();
    if (SaveButton)
      SaveButton->draw();
    renderer->draw();
    UnitSelection->draw();
    if (AnimationSelection) {
      AnimationSelection->draw();
      PauseButton->draw();
    }
    fps->draw();
  };
  w.run();

  Iyathuum::DatabaseTerminator::terminateAll();
}