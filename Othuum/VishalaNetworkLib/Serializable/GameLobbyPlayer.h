#pragma once

#include <string>
#include <array>
#include <vector>

#include "Lobby/LobbyPlayerModel.h"
#include "VishalaNetworkLib/Core/Serialization.h"

namespace Vishala {
  class GameLobbyPlayer : public Serialization {
  public:
    LobbyPlayerModel lobbyIdentification;

    virtual BinaryPackage toBinary()                override;
    virtual void fromBinary(BinaryPackage& Package) override;
    virtual nlohmann::json toJson()                 override;
    virtual void fromJson(nlohmann::json)           override;
  };
}