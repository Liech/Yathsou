#include "DedicatedServer.h"
#include "VishalaNetworkLib/Core/Connection.h"
#include "DedicatedServerConfiguration.h"
#include "Scene.h"
#include "Entity.h"
#include "Components/Transform2D.h"
#include "Components/Dot.h"
#include <filesystem>

#include <iostream>

namespace Uyanah {
  DedicatedServer::DedicatedServer() {
    _config = std::make_unique<DedicatedServerConfiguration>();
    createTestScene();
  }

  DedicatedServer::~DedicatedServer() {
    _stop = true;
    _thread.wait();
  }

  void DedicatedServer::setConfig(DedicatedServerConfiguration config) {
    _config = std::make_unique<DedicatedServerConfiguration>(config);
  }

  void DedicatedServer::start() {
    _connection = std::make_unique<Vishala::Connection>();
    _connection->setAcceptConnection(true);
    _connection->setChannelCount(1);
    _connection->setMaximumConnectionCount(64);
    _connection->setPort(_config->welcomePort);
    _connection->setConnectionFailedCallback([this](std::string ip, int port) {});
    _connection->setDisconnectCallback([this](size_t client) {std::cout << ":(" << std::endl;     });
    _connection->setRecievedCallback(0, [this](size_t client, std::unique_ptr<Vishala::BinaryPackage> package) {});
    _connection->setNewConnectionCallback([this](size_t client, std::string ip, int port) {std::cout << ":)" << std::endl;  });
    bool ok = _connection->start();
    if (!ok)
      throw std::runtime_error("Port used");
    std::cout << "Dedicated Server awaiting connections" << std::endl;


    _stop = false;
    _thread = std::async(std::launch::async, [this]() {runThread(); });
  }

  void DedicatedServer::stop() {
    _stop = true;
  }

  void DedicatedServer::runThread() {
    while (!_stop) {
      _connection->update();
    }
  }

  void DedicatedServer::createTestScene() {
    _scene = std::make_unique<Scene>();
    if (!std::filesystem::exists("savegame.json")) {
      Entity a;
      std::shared_ptr<Components::Transform2D> aTransform = std::make_shared<Components::Transform2D>();
      aTransform->position = glm::vec2(5, 5);
      std::shared_ptr<Components::Dot> aDot = std::make_shared<Components::Dot>();
      a.components.push_back(aTransform);
      a.components.push_back(aDot);

      Entity b;
      std::shared_ptr<Components::Transform2D> bTransform = std::make_shared<Components::Transform2D>();
      bTransform->position = glm::vec2(7, 5);
      std::shared_ptr<Components::Dot> bDot = std::make_shared<Components::Dot>();
      b.components.push_back(bTransform);
      b.components.push_back(bDot);

      _scene->objects.push_back(a);
      _scene->objects.push_back(b);
      _scene->toJsonFile("savegame.json");
    }
    else
      _scene->fromJsonFile("savegame.json");
  }
}