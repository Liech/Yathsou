#pragma once

#include "Core/Serialization.h"
#include "LobbyGame.h"
#include "LobbyPlayerModel.h"
#include "Serializable/Client2LobbyMessage.h"
#include <vector>

namespace Vishala {

  class LobbyModel : public Serialization {
  public:
    std::vector<LobbyGame>           openGames   ;
    std::vector<LobbyPlayerModel>    players     ;
    std::vector<Client2LobbyMessage> openRequests;

    size_t                           nextPlayerNumber = 0;
    size_t                           nextGameNumber   = 0;

    virtual nlohmann::json           toJson()                   override;
    virtual void                     fromJson(nlohmann::json)   override;
    virtual BinaryPackage            toBinary()                 override;
    virtual void                     fromBinary(BinaryPackage&) override;
  };
}