#pragma once

#include "Core/Serialization.h"
#include "Serializable/Acknowledgement.h"
#include "Serializable/LobbyBriefing.h"
#include "Serializable/GameLobbyStateUpdate.h"

namespace Vishala {

  class Lobby2ClientMessage : public Serialization {
  public:
    const std::string Name() const override { return "Lobby2ClientMessage"; }
    enum class Type : int {
      Acknowledgment, LobbyBriefing, GameClosed, LobbyUpdate, GameLobbyUpdate, StartGame
    };
    class Nothing {};
    Lobby2ClientMessage();
    ~Lobby2ClientMessage();

    Type            type = Type::Acknowledgment;
    //union
    //{
      Acknowledgement      acknowledgment ;
      LobbyBriefing        lobbyBriefing  ;
      LobbyStateUpdate     lobbyUpdate    ;
      GameLobbyStateUpdate gameLobbyUpdate;
      Nothing              nothing        ;
    //};

    virtual nlohmann::json             toJson()        const          override;
    virtual void                       fromJson(nlohmann::json)  override;
    virtual BinaryPackage              toBinary()      const          override;
    virtual void                       fromBinary(BinaryPackage&) override;
  };
}