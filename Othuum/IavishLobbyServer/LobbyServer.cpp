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
    while (true) 
      _lobby->update();
  }
}