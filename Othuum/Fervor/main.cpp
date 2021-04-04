#include <iostream>

#include "IyathuumCoreLib/Singleton/Database.h"
#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Core/Camera.h"
#include "AhwassaGraphicsLib/Drawables/Background.h"

#include "AhwassaGraphicsLib/BasicRenderer/BasicBoxRenderer.h"
#include "AhwassaGraphicsLib/Uniforms/Texture.h"
#include "AezeselFileIOLib/ImageIO.h"

#include "AhwassaGraphicsLib/VR/VR.h"

int main(int argc, char** argv) {
  int width  = 800;
  int height = 600;
  Ahwassa::Window w(width, height);
  Ahwassa::Background b(&w);

  std::shared_ptr<Ahwassa::Camera> cam = std::make_shared<Ahwassa::Camera>("camera",width,height);
  //Ahwassa::VR vr;

  auto img = Aezesel::ImageIO::readImage("Data/Textures/Map.png");

  std::unique_ptr<Ahwassa::Texture> texture;
  std::shared_ptr < Ahwassa::BasicBoxRenderer> box;
  //std::vector<std::shared_ptr<Ahwassa::InstancedText>> handle;

  //std::unique_ptr<Ahwassa::InstancedTextRenderer> g;
  w.Startup = [&]() {
    //g = std::make_unique<Ahwassa::InstancedTextRenderer>(&w);
    texture = std::make_unique<Ahwassa::Texture>("Map",img.get());
    box = std::make_unique<Ahwassa::BasicBoxRenderer>(cam);
    //for (int i = 0; i < 1; i++) {
    //  handle.push_back(g->newText("Hallo Welt",glm::vec2(50,50),2));
    //}
  };

  w.Update = [&]() {
    b.draw();
    //vr.update();
    //for (int i = 0; i < 10000; i++) {
    //  auto rec = Iyathuum::glmAABB<2>(glm::vec2(rand() % width, rand() % height), glm::vec2(rand() % 10 + 10, rand() % 10 + 10));
    //  auto clr = Iyathuum::Color(rand() % 255, rand() % 255, rand() % 255);
    //  handle[i]->location = rec;
    //}
    box->start();
    box->drawDot(glm::vec3(0, 0, 0.0f), glm::vec3(0.1f, 0.1f, 0.1f), Iyathuum::Color(255, 0, 0));
    box->end();

    //g->draw();
  };
  w.run();

  Iyathuum::DatabaseTerminator::terminateAll();
}