#include <iostream>

#include "IyathuumCoreLib/Singleton/Database.h"
#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Core/Camera.h"
#include "AhwassaGraphicsLib/Drawables/Background.h"

#include "AhwassaGraphicsLib/InstancedRenderer/InstancedBoxRenderer.h"
#include "AhwassaGraphicsLib/InstancedRenderer/IInstancedBox.h"
#include "AhwassaGraphicsLib/InstancedRenderer/InstancedDot.h"
#include "AhwassaGraphicsLib/InstancedRenderer/InstancedBox.h"
#include "AhwassaGraphicsLib/Uniforms/Texture.h"
#include "AezeselFileIOLib/ImageIO.h"

#include <IyathuumCoreLib/lib/glm/gtc/matrix_transform.hpp>
#include "AhwassaGraphicsLib/VR/VR.h"

int main(int argc, char** argv) {
  int width  = 800;
  int height = 600;
  Ahwassa::Window w(width, height);
  Ahwassa::Background b(&w);

  std::shared_ptr<Ahwassa::Camera> cam = std::make_shared<Ahwassa::Camera>("camera",width,height);
  //Ahwassa::VR vr;

  auto img = Aezesel::ImageIO::readImage("Data/Textures/Map.png");

  std::vector < std::shared_ptr<Ahwassa::InstancedDot>> handle;
  std::shared_ptr < Ahwassa::InstancedBoxRenderer> box;

  w.Startup = [&]() {
    //g = std::make_unique<Ahwassa::InstancedTextRenderer>(&w);
    box = std::make_unique<Ahwassa::InstancedBoxRenderer>(cam);
    for (int i = 0; i < 50000; i++) {
      handle.push_back(box->newDot(glm::vec3(0,0,0), 0.1f));
    }
  };

  w.Update = [&]() {
    b.draw();
    //vr.update();
    for (int i = 0; i < 50000; i++) {
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
  };
  w.run();

  Iyathuum::DatabaseTerminator::terminateAll();
}