#include "Client.h"
#include "VishalaNetworkLib/Core/Connection.h"
#include "VishalaNetworkLib/Core/ConnectionMultiplexer.h"
#include "ClientConfiguration.h"

#include <iostream>
#include "Scene.h"
#include "Entity.h"
#include "Components/Transform2D.h"
#include "Commands/Command.h"
#include "Components/Dot.h"
#include <filesystem>

namespace Uyanah {

  Client::Client() {
    _config = std::make_unique<ClientConfiguration>();
    _connection = std::shared_ptr< Vishala::Connection>();
  }

  Client::~Client() {
    _stop = true;
  }

  void Client::setConfig(ClientConfiguration config) {
    _config = std::make_unique<ClientConfiguration>(config);
  }

  void Client::start() {
    _connection = std::make_shared<Vishala::Connection>();
    _connection->setAcceptConnection(true);
    _connection->setChannelCount(3);
    _connection->setMaximumConnectionCount(64);
    int port = _config->myPort;
    _connection->setPort(port);
    _connection->setConnectionFailedCallback([this](std::string ip, int port) {});
    _connection->setDisconnectCallback([this](size_t client) {std::cout << ":(" << std::endl;     });
    _connection->setRecievedCallback(0, [this](size_t client, std::unique_ptr<Vishala::BinaryPackage> package) {});
    _connection->setNewConnectionCallback([this](size_t client, std::string ip, int port) {std::cout << ":)" << std::endl;  });
    bool ok = _connection->start();
    int tests = 50;
    while (!ok && tests > 0) {
      port++;
      tests--;
      _connection->setPort(port);
      ok = _connection->start();
    }
    if (!ok)
      throw std::runtime_error("Could not find free port");

    _connection->connectNonblocking(_config->serverPort, _config->serverIP);

    _multiplexer = std::make_shared<Vishala::ConnectionMultiplexer>(1,_connection);
    _scene = std::make_unique<Scene>();

    _connection->setRecievedCallback(2, [this](size_t client, std::unique_ptr<Vishala::BinaryPackage> package) {
      auto cmd = Vishala::Serialization::deserializeCast<Uyanah::Commands::Command>(*package);
      cmd->apply(*_scene);
    });
  }

  void Client::stop() {
    _stop = true;
  }

  void Client::update() {
    if (_connection)
      _connection->update();
    _scene->update();
  }

  const Scene& Client::getScene() {
    if (!_scene)
      return Scene();
    return *_scene;
  }

  void Client::send(size_t channel, const Vishala::BinaryPackage& p) {
    for (auto c : _connection->getAllConnections()) {
      _connection->send(c, channel, std::make_unique<Vishala::BinaryPackage>(p));
    }
  }
}