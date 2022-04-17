#pragma once

#include "Core/Serialization.h"
#include "LobbyGame.h"
#include "LobbyPlayerModel.h"
#include "OpenLobbyRequest.h"
#include "Serializable/Client2LobbyMessage.h"
#include <vector>

namespace Vishala { 
  class LobbyModel : public Serialization {
  public:
    const std::string Name() const override { return "LobbyModel"; }
    std::vector<LobbyGame>        openGames   ;
    std::vector<LobbyPlayerModel> players     ;
    std::vector<OpenLobbyRequest>      openRequests;

    size_t                           nextPlayerNumber = 0;
    size_t                           nextGameNumber   = 0;

    virtual nlohmann::json           toJson()      const             override;
    virtual void                     fromJson(nlohmann::json)   override;
    virtual BinaryPackage            toBinary()     const            override;
    virtual void                     fromBinary(BinaryPackage&) override;
  };
}