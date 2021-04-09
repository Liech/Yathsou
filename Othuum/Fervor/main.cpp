#include <iostream>

#include "IyathuumCoreLib/Singleton/Database.h"
#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Core/Camera.h"
#include "AhwassaGraphicsLib/Drawables/Background.h"
#include "AhwassaGraphicsLib/Drawables/FPS.h"
#include "AhwassaGraphicsLib/Input/Input.h"
#include "AhwassaGraphicsLib/Input/FreeCamera.h"

#include <IyathuumCoreLib/lib/glm/gtc/matrix_transform.hpp>

#include "AhwassaGraphicsLib/Renderer/DiffuseMeshRenderer.h"
#include "AhwassaGraphicsLib/Util.h"
#include "AthanahCommonLib/SupComMeshLoader.h"
#include "AthanahCommonLib/SupComMeshRenderer.h"
#include "AthanahCommonLib/SupComModel.h"


int main(int argc, char** argv) {
  int width  = 800;
  int height = 600;
  Ahwassa::Window w(width, height);
  Ahwassa::Background b(&w);
  std::unique_ptr<Ahwassa::FPS> fps;

  std::shared_ptr<Ahwassa::FreeCamera> freeCam;
  std::shared_ptr<Athanah::SupComMeshRenderer> renderer;
  std::shared_ptr<Athanah::SupComModel> model = std::shared_ptr<Athanah::SupComModel>();
  std::shared_ptr<Athanah::SupComMesh> mesh = std::shared_ptr<Athanah::SupComMesh>();
  w.Startup = [&]() {
    renderer = std::make_shared<Athanah::SupComMeshRenderer>(w.camera());
    std::string unit = "UEL0208";
    model = std::make_shared<Athanah::SupComModel>("C:\\Users\\nicol\\Desktop\\units\\",unit);

    mesh = std::make_shared<Athanah::SupComMesh>();
    mesh->teamColor = Iyathuum::Color(0 , 255, 255);
    mesh->transformation = glm::mat4(1.0);
    mesh->model = model;

    renderer->addMesh(mesh); 
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