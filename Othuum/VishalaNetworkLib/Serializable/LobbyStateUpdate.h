#pragma once

#include <string>
#include <array>
#include <vector>

#include "LobbyGame.h"
#include "Serialization.h"

namespace Vishala {
  class LobbyStateUpdate : public Serialization {
  public:
    std::vector<LobbyGame> openGames;

    virtual BinaryPackage toBinary()                override;
    virtual void fromBinary(BinaryPackage& Package) override;
    virtual nlohmann::json toJson()                 override;
    virtual void fromJson(nlohmann::json)           override;
  };
}