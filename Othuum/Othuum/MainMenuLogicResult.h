#pragma once

#include <vector>
#include "VishalaNetworkLib/Core/Connection.h"
#include "VishalaNetworkLib/Serializable/GameLobbyPlayer.h"
#include "UyanahGameServer/DedicatedServer.h"
#include "UyanahGameServer/Client.h"

class MainMenuLogicResult{
public:
  bool hostServer      = false;
  int  serverPort      = 6112;
  std::string serverIP = "localhost";
  int  myPort          = 6114;
};