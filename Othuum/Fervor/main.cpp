#include <iostream>
#include <filesystem>

#include "IyathuumCoreLib/Singleton/Database.h"
#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Core/Camera.h"
#include "AhwassaGraphicsLib/Core/DeferredComposer.h"
#include "AhwassaGraphicsLib/Drawables/Background.h"
#include "AhwassaGraphicsLib/Drawables/FPS.h"
#include "AhwassaGraphicsLib/Input/Input.h"
#include "AhwassaGraphicsLib/Input/FreeCamera.h"
#include "AhwassaGraphicsLib/BasicRenderer/BasicTexture2DRenderer.h"
#include "AhwassaGraphicsLib/BufferObjects/FBO.h"
#include "AthanahCommonLib/Bloom.h"

#include <IyathuumCoreLib/lib/glm/gtc/matrix_transform.hpp>

#include "AhwassaGraphicsLib/Util.h"
#include "AthanahCommonLib/SupComMeshLoader.h"
#include "AthanahCommonLib/SupComMeshRendererDef.h"
#include "AthanahCommonLib/SupComModel.h"
#include "AthanahCommonLib/SupComModelFactory.h"

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
  int width = 800;
  int height = 600;
  //int height = 1500;
  //int width = 2500;

  Ahwassa::Window w(width, height);
  Ahwassa::Background b(&w);
  std::unique_ptr<Ahwassa::FPS> fps;

  std::shared_ptr<Ahwassa::FreeCamera> freeCam;
  std::shared_ptr<Athanah::SupComMeshRendererDef> renderer;
  std::shared_ptr<Ahwassa::DeferredComposer> composer;
  std::shared_ptr<Ahwassa::BasicTexture2DRenderer> textureRenderer;
  std::shared_ptr<Athanah::SupComModel> model = std::shared_ptr<Athanah::SupComModel>();
  std::vector<std::shared_ptr<Athanah::SupComMesh>> meshes;
  std::shared_ptr<Athanah::Bloom> bloom;
  std::string animName;

  std::string pc = "C:\\Users\\nicol\\Desktop\\units\\";
  std::string lpt = "C:\\Users\\Niki\\Desktop\\units\\";
  std::string unit = "UAL0401";
  //scout "UAL0101";
  //engi"UEL0208";
  Athanah::SupComModelFactory factory (lpt);
  Athanah::BlueprintFactory blueprints(lpt);
  auto blueprint = blueprints.loadModel(unit);
  std::cout<< blueprint->description()<<std::endl;

  w.Startup = [&]() {
    renderer = std::make_shared<Athanah::SupComMeshRendererDef>(w.camera());
    composer = std::make_shared<Ahwassa::DeferredComposer>(&w,width, height);
    textureRenderer = std::make_shared< Ahwassa::BasicTexture2DRenderer>(&w);
    int animationNumber = 4;
    bloom = std::make_shared<Athanah::Bloom>(&w, width, height);

    //model = std::make_shared<Athanah::SupComModel>(pc, unit);
    model = factory.loadModel(unit);
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
    meshes[1]->transformation = glm::rotate(glm::translate(glm::mat4(1.0), glm::vec3(100, 0, 0)), t, glm::vec3(0, 1, 0)) ;
    
    composer->start();
    renderer->draw();
    composer->end();
    bloom->draw(composer->getResult(), composer->getRawTextures()[3], 1);
    b.draw();

    textureRenderer->start();
    auto loc  = Iyathuum::glmAABB<2>(glm::vec2(  0               , 0                ), glm::vec2(w.getWidth() / 3, w.getHeight() / 3));
    auto loc2 = Iyathuum::glmAABB<2>(glm::vec2(  w.getWidth() / 3, 0                ), glm::vec2(w.getWidth() / 3, w.getHeight() / 3));
    auto loc3 = Iyathuum::glmAABB<2>(glm::vec2(  0               , w.getHeight() / 3), glm::vec2(w.getWidth() / 3, w.getHeight() / 3));
    auto loc4 = Iyathuum::glmAABB<2>(glm::vec2(  w.getWidth() / 3, w.getHeight() / 3), glm::vec2(w.getWidth() / 3, w.getHeight() / 3));
    auto loc5 = Iyathuum::glmAABB<2>(glm::vec2(2 * w.getWidth() / 3, w.getHeight() / 3), glm::vec2(w.getWidth() / 3, w.getHeight() / 3));
    auto loc6 = Iyathuum::glmAABB<2>(glm::vec2(2 * w.getWidth() / 3, 0), glm::vec2(w.getWidth() / 3, w.getHeight() / 3));
    textureRenderer->draw(*composer->getRawTextures()[0], loc , true);
    textureRenderer->draw(*composer->getRawTextures()[1], loc2, true);
    textureRenderer->draw(*composer->getRawTextures()[2], loc3, true);
    textureRenderer->draw(*composer->getRawTextures()[3], loc4, true);
    textureRenderer->draw(*composer->getResult(), loc5, true);
    textureRenderer->draw(*bloom->getResult()   , loc6, true);
    textureRenderer->end();
    

    fps->draw();
  };
  w.run();

  Iyathuum::DatabaseTerminator::terminateAll();
}