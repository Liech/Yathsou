#pragma once

#include <string>
#include <array>
#include <vector>

#include "Lobby/LobbyPlayerModel.h"
#include "VishalaNetworkLib/Core/Serialization.h"

namespace Vishala {
  class GameLobbyPlayer : public Serialization {
  public:
    const std::string Name() const override { return "GameLobbyPlayer"; }

    LobbyPlayerModel lobbyIdentification;

    virtual BinaryPackage toBinary()   const        override;
    virtual void fromBinary(BinaryPackage& Package) override;
    virtual nlohmann::json toJson()    const        override;
    virtual void fromJson(nlohmann::json)           override;
  };
}