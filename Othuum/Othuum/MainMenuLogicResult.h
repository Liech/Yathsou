#pragma once

#include <vector>
#include "VishalaNetworkLib/Core/Connection.h"
#include "VishalaNetworkLib/Serializable/GameLobbyPlayer.h"
#include "UyanahGameServer/DedicatedServer.h"
#include "UyanahGameServer/Client.h"

class MainMenuLogicResult{
public:
  struct Player {
    std::unique_ptr<Vishala::Connection> _connection;
    size_t                               _id        ;
    Vishala::GameLobbyPlayer             _info      ;
  };

  std::unique_ptr<Uyanah::DedicatedServer> _server;
  std::unique_ptr<Uyanah::Client         > _client;
  std::vector<MainMenuLogicResult::Player> _otherPlayers;
  MainMenuLogicResult::Player              _self        ; //connection = nullptr

};