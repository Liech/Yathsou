#include "OthuumGame.h"

#include "UyanahGameServer/Scene.h"
#include "ClientControl.h"
#include "VishalaNetworkLib/Protocoll/AuthoritarianGameServer.h"

#include "UyanahGameServer/Components/Dot.h"
#include "UyanahGameServer/Components/Transform2D.h"
#include "UyanahGameServer/Commands/UpdateScene.h"



OthuumGame::OthuumGame() {
  _client = nullptr;
  _scene  = std::make_shared<Uyanah::Scene>();
  _timer = std::make_unique<Iyathuum::UpdateTimer>([this]() {tick(); }, 30);

}

void OthuumGame::tick() {
  _control->update();
  if (_client)
    _client->update();
}

void OthuumGame::update() {
  if (_server)
    _server->update();
  if (_control)
    _timer->update();
}

void OthuumGame::createServer(int port) {
  std::unique_ptr<Uyanah::Scene> scene = std::make_unique<Uyanah::Scene>();

  Uyanah::Entity a;
  std::shared_ptr<Uyanah::Components::Transform2D> aTransform = std::make_shared<Uyanah::Components::Transform2D>();
  aTransform->position = glm::vec2(5, 5);
  std::shared_ptr<Uyanah::Components::Dot> aDot = std::make_shared<Uyanah::Components::Dot>();
  a.addComponent(aTransform);
  a.addComponent(aDot);

  for (int i = 0; i < 6; i++) {
    Uyanah::Entity b;
    std::shared_ptr<Uyanah::Components::Transform2D> bTransform = std::make_shared<Uyanah::Components::Transform2D>();
    bTransform->position = glm::vec2(rand() % 300, rand() % 300);
    std::shared_ptr<Uyanah::Components::Dot> bDot = std::make_shared<Uyanah::Components::Dot>();
    b.addComponent(bTransform);
    b.addComponent(bDot);
    scene->objects.push_back(b);
  }
  scene->objects.push_back(a);

  _server = std::make_unique<Vishala::AuthoritarianGameServer>(std::move(scene), port, 30);
  _server->addOnUpdate(std::make_unique<Uyanah::Commands::UpdateScene>());
}