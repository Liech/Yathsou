#include "Client.h"
#include "VishalaNetworkLib/Core/Connection.h"
#include "ClientConfiguration.h"

#include <iostream>


namespace Uyanah {

  Client::Client() {
    _config = std::make_unique<ClientConfiguration>();
  }

  Client::~Client() {
    _stop = true;
    _thread.wait();
  }

  void Client::setConfig(ClientConfiguration config) {
    _config = std::make_unique<ClientConfiguration>(config);
  }

  void Client::start() {
    _connection = std::make_unique<Vishala::Connection>();
    _connection->setAcceptConnection(true);
    _connection->setChannelCount(1);
    _connection->setMaximumConnectionCount(64);
    _connection->setPort(_config->myPort);
    _connection->setConnectionFailedCallback([this](std::string ip, int port) {});
    _connection->setDisconnectCallback([this](size_t client) {std::cout << ":(" << std::endl;     });
    _connection->setRecievedCallback(0, [this](size_t client, std::unique_ptr<Vishala::BinaryPackage> package) {});
    _connection->setNewConnectionCallback([this](size_t client, std::string ip, int port) {std::cout << ":)" << std::endl;  });
    bool ok = _connection->start();
    if (!ok)
      throw std::runtime_error("Port used");

    _thread = std::async(std::launch::async, [this]() {runThread(); });
    _connection->connectNonblocking(_config->serverPort, _config->serverIP);

  }

  void Client::stop() {
    _stop = true;
  }

  void Client::runThread() {
    while (!_stop) {
      _connection->update();
    }
  }

}