#pragma once

#include "Core/Serialization.h"
#include "LobbyGame.h"
#include "LobbyPlayerModel.h"
#include "Serializable/Client2LobbyMessage.h"
#include <vector>

namespace Vishala {

  class OpenLobbyRequest : public Serialization {
  public:
    const std::string Name() const override { return "OpenLobbyRequest"; }

    OpenLobbyRequest();
    OpenLobbyRequest(size_t playerNumber, Client2LobbyMessage request);

    size_t              playerNumber;
    Client2LobbyMessage request;

    virtual nlohmann::json           toJson()       const            override;
    virtual void                     fromJson(nlohmann::json)   override;
    virtual BinaryPackage            toBinary()     const            override;
    virtual void                     fromBinary(BinaryPackage&) override;
  };
}