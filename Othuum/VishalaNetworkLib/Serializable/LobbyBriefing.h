#pragma once

#include <string>
#include <array>
#include <vector>

#include "Serialization.h"
#include "LobbyStateUpdate.h"

namespace Vishala {
  class LobbyBriefing : public Serialization{
  public:
    int               playerId    = 0;
    LobbyStateUpdate  lobbyStatus   ;

    virtual BinaryPackage toBinary()                override;
    virtual void fromBinary(BinaryPackage& Package) override;
    virtual nlohmann::json toJson()                 override;
    virtual void fromJson(nlohmann::json)           override;

  };
}