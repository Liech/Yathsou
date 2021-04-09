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

int main(int argc, char** argv) {
  int width  = 800;
  int height = 600;
  Ahwassa::Window w(width, height);
  Ahwassa::Background b(&w);
  std::unique_ptr<Ahwassa::FPS> fps;

  std::shared_ptr<Ahwassa::FreeCamera> freeCam;
  std::shared_ptr<Ahwassa::DiffuseMeshRenderer> renderer;
  std::shared_ptr<Ahwassa::DiffuseMeshRendererMesh> mesh  = std::make_shared< Ahwassa::DiffuseMeshRendererMesh>();
  w.Startup = [&]() {
    renderer = std::make_shared<Ahwassa::DiffuseMeshRenderer>(w.camera());
    mesh->mesh = Ahwassa::Util::getCube();
    mesh->color = Iyathuum::Color(255, 0, 0);
    mesh->transformation = glm::mat4(1);


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