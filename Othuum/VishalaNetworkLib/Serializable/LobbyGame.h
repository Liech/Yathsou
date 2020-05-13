#pragma once

#include <string>
#include <vector>
#include "GameRoomPlayer.h"

#include "Core/Serialization.h"

namespace Vishala {
  class LobbyGame : public Serialization {
  public:
    std::string name              ;
    int         numberOfPlayers   ;
    int         maxNumberOfPlayers;

    virtual BinaryPackage toBinary()                override;
    virtual void fromBinary(BinaryPackage& Package) override;
    virtual nlohmann::json toJson()                 override;
    virtual void fromJson(nlohmann::json)           override;
  };
}