#include "DedicatedServer.h"
#include "VishalaNetworkLib/Core/Connection.h"
#include "DedicatedServerConfiguration.h"
#include "Scene.h"
#include "Entity.h"
#include "Components/Transform2D.h"
#include "Components/Dot.h"
#include <filesystem>
#include "IyathuumCoreLib/Util/UpdateTimer.h"

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
    _connection->setChannelCount(2);
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

  }

  void DedicatedServer::stop() {
    _stop = true;
  }

  void DedicatedServer::newConnection(size_t player) {
    _scene->newTarget(player);
  }

  void DedicatedServer::runThread() {
    float time = 0;
    int ticksPerSecond = 60;
    Iyathuum::UpdateTimer timer([this,&time, ticksPerSecond]() {
      time += 1 / (float)ticksPerSecond;
      glm::vec2 pos = glm::vec2(std::sin(time) * 100 + 300, std::cos(time) * 100 + 300);
      Scene* s = &_scene->Data;
      if (s->objects.size() == 0)
        return;
      Entity* e = &s->objects[0];
      if (e->components.size() == 0)
        return;
      std::shared_ptr<Component> c = e->components[0];
      std::shared_ptr<Components::Transform2D> t = std::dynamic_pointer_cast<Components::Transform2D>(c);
      if (t)
        t->position = pos;
      _scene->changed();
    }, ticksPerSecond);
    timer.setStallCall([](int x) {std::cout << "Stall " << x <<std::endl; });
    while (!_stop) {
      _connection->update();
      _scene->update();
      timer.update();
    }
  }

  void DedicatedServer::createTestScene() {
    _scene = std::make_unique<Vishala::NetworkMemoryWriter<Scene>>(1,_connection);
    //if (!std::filesystem::exists("savegame.json")) {
      Entity a;
      std::shared_ptr<Components::Transform2D> aTransform = std::make_shared<Components::Transform2D>();
      aTransform->position = glm::vec2(5, 5);
      std::shared_ptr<Components::Dot> aDot = std::make_shared<Components::Dot>();
      a.components.push_back(aTransform);
      a.components.push_back(aDot);

      for (int i = 0; i < 600; i++) {
        Entity b;
        std::shared_ptr<Components::Transform2D> bTransform = std::make_shared<Components::Transform2D>();
        bTransform->position = glm::vec2(rand() %300,  rand() % 300);
        std::shared_ptr<Components::Dot> bDot = std::make_shared<Components::Dot>();
        b.components.push_back(bTransform);
        b.components.push_back(bDot);
        _scene->Data.objects.push_back(b);
      }
      _scene->Data.objects.push_back(a);
      _scene->Data.toJsonFile("savegame.json");
    //}
    //else
    //  _scene->Data.fromJsonFile("savegame.json");
    _scene->changed();
  }
}