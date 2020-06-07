#pragma once

#include "Core/Serialization.h"
#include "LobbyGame.h"
#include "LobbyPlayerModel.h"
#include "Serializable/Client2LobbyMessage.h"
#include <vector>

namespace Vishala {

  class OpenLobbyRequest : public Serialization {
  public:
    OpenLobbyRequest();
    OpenLobbyRequest(size_t playerNumber, Client2LobbyMessage request);

    size_t              playerNumber;
    Client2LobbyMessage request;

    virtual nlohmann::json           toJson()                   override;
    virtual void                     fromJson(nlohmann::json)   override;
    virtual BinaryPackage            toBinary()                 override;
    virtual void                     fromBinary(BinaryPackage&) override;
  };
}