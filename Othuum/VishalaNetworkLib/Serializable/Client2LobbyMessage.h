#pragma once

#include "Core/Serialization.h"

#include "CreateGameRequest.h"

namespace Vishala {

  class Client2LobbyMessage : public Serialization {
  public:
    enum class Type : int {
      Refresh, CreateGame, JoinGame
    };
    class Nothing{};
    Client2LobbyMessage();
    Client2LobbyMessage(const Client2LobbyMessage& req);
    ~Client2LobbyMessage();

    Type            type   = Type::Refresh;
    union
    {
      CreateGameRequest createGame;
      Nothing           nothing   ;
    };


    virtual nlohmann::json             toJson()                  override;
    virtual void                       fromJson(nlohmann::json)  override;
    virtual BinaryPackage              toBinary()                override;
    virtual void                       fromBinary(BinaryPackage&) override;
  };
}