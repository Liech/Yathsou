#include "DedicatedServer.h"
#include "VishalaNetworkLib/Core/Connection.h"
#include "DedicatedServerConfiguration.h"
#include "Scene.h"
#include "Entity.h"
#include "Components/Transform2D.h"
#include "Components/Dot.h"
#include <filesystem>
#include "IyathuumCoreLib/Util/UpdateTimer.h"
#include "Commands/Initialize.h"

#include <iostream>

namespace Uyanah {
  DedicatedServer::DedicatedServer() {
    _config = std::make_unique<DedicatedServerConfiguration>();
  }

  DedicatedServer::~DedicatedServer() {
    _stop = true;
    _thread.wait();
  }

  void DedicatedServer::setConfig(DedicatedServerConfiguration config) {
    _config = std::make_unique<DedicatedServerConfiguration>(config);
  }

  void DedicatedServer::start() {
    _connection = std::make_shared<Vishala::Connection>();
    _connection->setAcceptConnection(true);
    _connection->setChannelCount(3);
    _connection->setMaximumConnectionCount(64);
    _connection->setPort(_config->welcomePort);
    _connection->setConnectionFailedCallback([this](std::string ip, int port) {});
    _connection->setDisconnectCallback([this](size_t client) {std::cout << ":(" << std::endl;     });
    _connection->setRecievedCallback(0, [this](size_t client, std::unique_ptr<Vishala::BinaryPackage> package) {});
    _connection->setNewConnectionCallback([this](size_t client, std::string ip, int port) {
      newConnection(client);
      });
    bool ok = _connection->start();
    if (!ok)
      throw std::runtime_error("Port used");
    std::cout << "Dedicated Server awaiting connections" << std::endl;


    _stop = false;
    _thread = std::async(std::launch::async, [this]() {runThread(); });
    createTestScene();

    _connection->setRecievedCallback(2, [this](size_t client, std::unique_ptr<Vishala::BinaryPackage> package) {
      for (auto con : _connection->getAllConnections()) {
        std::unique_ptr<Vishala::BinaryPackage> p = std::make_unique<Vishala::BinaryPackage>(*package);
        _connection->send(con, 2, std::move(p));
      }
    });
  }

  void DedicatedServer::stop() {
    _stop = true;
  }

  void DedicatedServer::newConnection(size_t player) {
    Uyanah::Commands::Initialize cmd;
    cmd.scene = *_scene;
    _connection->send(player, 2, std::make_unique<Vishala::BinaryPackage>(cmd.serialize()));
  }

  void DedicatedServer::runThread() {
    float time = 0;
    auto start = std::chrono::steady_clock::now();

    int ticksPerSecond = 60;
    while (!_stop) {
      auto now = std::chrono::steady_clock::now();
      auto diff = now - start;
      auto end = now + std::chrono::milliseconds(16);
      _connection->update();
      std::this_thread::sleep_until(end);
    }
  }

  void DedicatedServer::createTestScene() {
    _scene = std::make_unique<Scene>();
    //if (!std::filesystem::exists("savegame.json")) {
    Entity a;
    std::shared_ptr<Components::Transform2D> aTransform = std::make_shared<Components::Transform2D>();
    aTransform->position = glm::vec2(5, 5);
    std::shared_ptr<Components::Dot> aDot = std::make_shared<Components::Dot>();
    a.addComponent(aTransform);
    a.addComponent(aDot);

    for (int i = 0; i < 600; i++) {
      Entity b;
      std::shared_ptr<Components::Transform2D> bTransform = std::make_shared<Components::Transform2D>();
      bTransform->position = glm::vec2(rand() %300,  rand() % 300);
      std::shared_ptr<Components::Dot> bDot = std::make_shared<Components::Dot>();
      b.addComponent(bTransform);
      b.addComponent(bDot);
      _scene->objects.push_back(b);
    }
    _scene->objects.push_back(a);
    _scene->toJsonFile("savegame.json");
  }
}