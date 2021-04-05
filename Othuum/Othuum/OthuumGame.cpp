#include "OthuumGame.h"

#include "ClientControl.h"
#include "VishalaNetworkLib/Protocoll/LiberalGameServer.h"
#include "ClientVisualization/ClientVisualization.h"
#include "InitializeCmd.h"

#include "AhwassaGraphicsLib/Drawables/FPS.h"
#include "AhwassaGraphicsLib/Drawables/Background.h"
#include "AhwassaGraphicsLib/Core/Window.h"

#include "UyanahGameServer/Scene.h"
#include "UyanahGameServer/Components/Dot.h"
#include "UyanahGameServer/Components/Transform2D.h"
#include "UyanahGameServer/Commands/UpdateScene.h"

OthuumGame::OthuumGame(Ahwassa::Window* w, bool authoritarian) {
  _authoritarian = authoritarian;
  _window = w;

  _authoClient = nullptr;
  _libClient   = nullptr;
  _scene  = std::make_shared<Uyanah::Scene>();
  _timer = std::make_unique<Iyathuum::UpdateTimer>([this]() {tick(); }, _fps);

  _vis = std::make_shared<ClientVisualization>(_scene,w);
  _list.push_back(std::make_shared<Ahwassa::Background>(w));
  _list.push_back(std::make_shared<Ahwassa::FPS>(w));
  _list.push_back(_vis);

  auto s = std::make_shared<Uyanah::Scene>();
  _timer->setTicksPerSecond(_fps);
  _control = std::make_shared<ClientControl>(
    [this](std::shared_ptr<Vishala::ICommand> cmd) {
    if (_authoritarian)
      _authoClient->sendCmd(*cmd);
    else
      _libClient->sendCmd(cmd);
    },s,w);
}

void OthuumGame::createClient(int myPort, int serverPort, std::string ip) {
  if (_authoritarian)
    _authoClient = std::make_unique<Vishala::AuthoritarianGameClient<Uyanah::Scene>>(_scene, _fps, myPort,serverPort,ip);
  else {
    _libClient = std::make_unique<Vishala::LiberalGameClient<Uyanah::Scene>>(_scene, _fps, myPort, serverPort, ip);
    _libClient->addOnUpdate(std::make_unique<Uyanah::Commands::UpdateScene>());
  }
}

void OthuumGame::tick() {
  _control->update();
}

void OthuumGame::update() {
  if (_authoClient)
    _authoClient->update();
  if (_libClient)
    _libClient->update();
  if (_authoServer)
    _authoServer->update();
  if (_libServer)
    _libServer->update();
  if (_control)
    _timer->update();
}

void OthuumGame::draw() {
  for (auto f : _list)
    f->draw();
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

  if (_authoritarian) {
    _authoServer = std::make_unique<Vishala::AuthoritarianGameServer>(std::move(scene), port, _fps);
    _authoServer->addOnUpdate(std::make_unique<Uyanah::Commands::UpdateScene>());
  }
  else {
    _libServer = std::make_unique<Vishala::LiberalGameServer>(std::move(scene), port, _fps);
    _libServer->addOnUpdate(std::make_unique<Uyanah::Commands::UpdateScene>());
    _libServer->setInitializationCommandCreator([this]() -> std::shared_ptr<Vishala::ICommand> {
      auto cmd = std::make_shared<InitializeCmd>();
      cmd->data = (Uyanah::Scene&)_libServer->data();
      return std::dynamic_pointer_cast<Vishala::ICommand>(cmd);
    });
  }
}

