#include <iostream>

#include "IyathuumCoreLib/Singleton/Database.h"
#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Core/Camera.h"
#include "AhwassaGraphicsLib/Drawables/Background.h"
#include "AhwassaGraphicsLib/Drawables/FPS.h"
#include "AhwassaGraphicsLib/Input/Input.h"
#include "AhwassaGraphicsLib/Input/FreeCamera.h"

#include "AhwassaGraphicsLib/Renderer/SphereRenderer.h"
#include "AhwassaGraphicsLib/Renderer/Sphere.h"
#include "AhwassaGraphicsLib/Uniforms/Texture.h"
#include "AezeselFileIOLib/ImageIO.h"
#include "AhwassaGraphicsLib/Widgets/Button.h"

#include <IyathuumCoreLib/lib/glm/gtc/matrix_transform.hpp>
#include "AhwassaGraphicsLib/VR/VR.h"

int main(int argc, char** argv) {
  int width  = 800;
  int height = 600;
  Ahwassa::Window w(width, height);
  Ahwassa::Background b(&w);
  std::unique_ptr<Ahwassa::FPS> fps;

  std::shared_ptr<Ahwassa::Camera> cam = std::make_shared<Ahwassa::Camera>("camera",width,height);
  std::shared_ptr<Ahwassa::FreeCamera> freeCam;
  //Ahwassa::VR vr;

  auto img = Aezesel::ImageIO::readImage("Data/Textures/Map.png");

  std::vector < std::shared_ptr<Ahwassa::Sphere>> handle;
  std::shared_ptr < Ahwassa::SphereRenderer> box;
  std::shared_ptr<Ahwassa::Button> button;

  w.Startup = [&]() {
    box = std::make_unique<Ahwassa::SphereRenderer>(cam);
    for (int i = 0; i < 100; i++) {
      handle.push_back(box->newSphere(glm::vec3(0,0,0), 0.1f));
    }
    freeCam = std::make_shared<Ahwassa::FreeCamera>(cam, w.input());
    w.input().addUIElement(freeCam);
    fps = std::make_unique<Ahwassa::FPS>(&w);
    button = std::make_shared<Ahwassa::Button>("Hallo", Iyathuum::glmAABB<2>(glm::vec2(50, 50), glm::vec2(200, 50)), []() {std::cout << "huhu" << std::endl; }, &w);
    w.input().addUIElement(button);
  };

  w.Update = [&]() {
    b.draw();
    //vr.update();
    for (int i = 0; i < 100; i++) {
      float x = (rand() % 1000) / 1000.00f;
      float y = (rand() % 1000) / 1000.00f;
      float z = (rand() % 1000) / 1000.00f;
      x *= 5; x -= 2.5f;
      y *= 5; y -= 2.5f;
      z *= 5; z -= 2.5f;
      handle[i]->setPosition(glm::vec3(x, y, z));
      handle[i]->setSize((rand() % 1000) / 5000.0f);
      handle[i]->setColor(Iyathuum::Color(rand() % 255, rand() % 255, rand() % 255));
    }

    box->draw();
    fps->draw();
    button->draw();
  };
  w.run();

  Iyathuum::DatabaseTerminator::terminateAll();
}