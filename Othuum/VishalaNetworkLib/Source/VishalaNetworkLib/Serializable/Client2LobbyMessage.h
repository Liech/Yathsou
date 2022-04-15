#pragma once

#include "Core/Serialization.h"

#include "CreateGameRequest.h"
#include "JoinGameRequest.h"

namespace Vishala {

  struct Client2LobbyMessage : public Serialization {
  public:
    const std::string Name() const override { return "Client2LobbyMessage"; }
    enum class Type : int {
      LobbyRefresh, CreateGame, JoinGame, LeaveGame, StartGame
    };
    struct Nothing{};
    Client2LobbyMessage();
    Client2LobbyMessage(const Client2LobbyMessage& req);
    ~Client2LobbyMessage();

    Type            type   = Type::LobbyRefresh;
    //union
    //{
      CreateGameRequest createGame;
      JoinGameRequest   joinGame  ;
      Nothing           nothing   ;
    //};


    virtual nlohmann::json             toJson()           const  override;
    virtual void                       fromJson(nlohmann::json)  override;
    virtual BinaryPackage              toBinary()         const  override;
    virtual void                       fromBinary(BinaryPackage&) override;
  };
}