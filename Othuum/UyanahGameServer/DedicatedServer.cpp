#include "DedicatedServer.h"
#include "VishalaNetworkLib/Core/Connection.h"
#include "DedicatedServerConfiguration.h"

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
}