#pragma once

#include <string>
#include <array>
#include <vector>

#include "Core/Serialization.h"
#include "LobbyStateUpdate.h"

namespace Vishala {
  class LobbyBriefing : public Serialization{
  public:
    const std::string Name() const override { return "LobbyBriefing"; }
    int               playerId    = 0;
    LobbyStateUpdate  lobbyStatus   ;

    virtual BinaryPackage toBinary()         const       override;
    virtual void fromBinary(BinaryPackage& Package) override;
    virtual nlohmann::json toJson()        const         override;
    virtual void fromJson(nlohmann::json)           override;

  };
}