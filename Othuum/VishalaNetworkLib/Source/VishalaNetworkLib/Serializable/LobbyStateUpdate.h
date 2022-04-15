#pragma once

#include <string>
#include <array>
#include <vector>

#include "Lobby/LobbyGame.h"
#include "Core/Serialization.h"

namespace Vishala {
  class LobbyStateUpdate : public Serialization {
  public:
    const std::string Name() const override { return "LobbyStateUpdate"; }
    std::vector<LobbyGame> openGames;

    virtual BinaryPackage toBinary()         const       override;
    virtual void fromBinary(BinaryPackage& Package) override;
    virtual nlohmann::json toJson()         const        override;
    virtual void fromJson(nlohmann::json)           override;
  };
}