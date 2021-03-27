#pragma once

#include <string>
#include <array>
#include <vector>

#include "GameLobbyPlayer.h"
#include "VishalaNetworkLib/Core/Serialization.h"

namespace Vishala {
  class GameLobbyStateUpdate : public Serialization {
  public:
    const std::string Name() const override { return "GameLobbyStateUpdate"; }
    std::vector<GameLobbyPlayer> currentPlayers;
    std::string                  gameName      ;
    bool                         gameStart     = false;
    int                          gameServerPort = 1234;
    std::string                  gameServerIP = "localhost";

    virtual BinaryPackage toBinary()               const override;
    virtual void fromBinary(BinaryPackage& Package)      override;
    virtual nlohmann::json toJson()                const override;
    virtual void fromJson(nlohmann::json)                override;
  };
}