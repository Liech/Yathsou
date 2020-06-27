#pragma once

#include <vector>
#include "VishalaNetworkLib/Core/Connection.h"
#include "VishalaNetworkLib/Serializable/GameLobbyPlayer.h"

class MainMenuLogicResult{
public:
  struct Player {
    std::unique_ptr<Vishala::Connection> _connection;
    size_t                               _id        ;
    Vishala::GameLobbyPlayer             _info      ;
  };

  std::vector<MainMenuLogicResult::Player> _otherPlayers;
  MainMenuLogicResult::Player              _self        ; //connection = nullptr

};