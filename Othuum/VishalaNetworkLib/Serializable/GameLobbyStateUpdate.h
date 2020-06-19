#pragma once

#include <string>
#include <array>
#include <vector>

#include "GameLobbyPlayer.h"
#include "VishalaNetworkLib/Core/Serialization.h"

namespace Vishala {
  class GameLobbyStateUpdate : public Serialization {
  public:
    std::vector<GameLobbyPlayer> currentPlayers;
    std::string                  gameName      ;

    virtual BinaryPackage toBinary()                override;
    virtual void fromBinary(BinaryPackage& Package) override;
    virtual nlohmann::json toJson()                 override;
    virtual void fromJson(nlohmann::json)           override;
  };
}