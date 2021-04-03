#include <iostream>

#include "IyathuumCoreLib/Singleton/Database.h"
#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Drawables/Background.h"

#include "AhwassaGraphicsLib/BasicRenderer/BasicTexture2DRenderer.h"
#include "AhwassaGraphicsLib/InstancedRenderer/InstancedRectangleRenderer.h"
#include "AhwassaGraphicsLib/InstancedRenderer/Rectangle.h"
#include "AhwassaGraphicsLib/Uniforms/Texture.h"
#include "AezeselFileIOLib/ImageIO.h"

#include "AhwassaGraphicsLib/VR.h"

int main(int argc, char** argv) {
  int width  = 800;
  int height = 600;
  Ahwassa::Window w(width, height);
  Ahwassa::Background b(&w);
  
  Ahwassa::VR vr;

  auto img = Aezesel::ImageIO::readImage("Data/Textures/Map.png");

  std::unique_ptr<Ahwassa::Texture> texture;
  std::shared_ptr < Ahwassa::BasicTexture2DRenderer> text;
  std::vector<std::shared_ptr<Ahwassa::Rectangle>> handle;

  std::unique_ptr<Ahwassa::InstancedRectangleRenderer> g;
  w.Startup = [&]() {
    //g = std::make_unique<Ahwassa::InstancedRectangleRenderer>(&w);
    texture = std::make_unique<Ahwassa::Texture>("Map",img.get());
    text = std::make_unique<Ahwassa::BasicTexture2DRenderer>(&w);
    //for (int i = 0; i < 10000; i++) {
    //  auto rec = Iyathuum::glmAABB<2>(glm::vec2(rand() % width, rand() % height), glm::vec2(rand()%10+10, rand()%10+10));
    //  auto clr = Iyathuum::Color(rand()%255, rand() % 255, rand() % 255);
    //  handle.push_back(g->newRectangle(rec, clr));
    //}
  };

  w.Update = [&]() {
    b.draw();
    vr.update();
    //for (int i = 0; i < 10000; i++) {
    //  auto rec = Iyathuum::glmAABB<2>(glm::vec2(rand() % width, rand() % height), glm::vec2(rand() % 10 + 10, rand() % 10 + 10));
    //  auto clr = Iyathuum::Color(rand() % 255, rand() % 255, rand() % 255);
    //  handle[i]->location = rec;
    //}
    text->start();
    text->draw(*texture,Iyathuum::glmAABB<2>(glm::vec2(50,50),glm::vec2(200,200)));
    text->end();

    //g->draw();
  };
  w.run();

  Iyathuum::DatabaseTerminator::terminateAll();
}