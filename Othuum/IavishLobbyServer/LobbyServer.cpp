#include "LobbyServer.h"

#include <iostream>

#include "VishalaNetworkLib/Serializable/ServerConfiguration.h"

namespace Iavish {
  void LobbyServer::run() {
    std::cout << "LobbyServer::run()" << std::endl;
    Vishala::ServerConfiguration config;

    config.fromJsonFile("ServerConfiguration.json");

    std::cout << "Init Lobby" << std::endl;
    _lobby = std::make_unique<Vishala::Server::Lobby>(config);

    auto start = std::chrono::steady_clock::now();
    while (true) {
      auto now = std::chrono::steady_clock::now();
      auto diff = now - start;
      auto end = now + std::chrono::milliseconds(16);
      _lobby->update();
      std::this_thread::sleep_until(end);
    }
  }
}