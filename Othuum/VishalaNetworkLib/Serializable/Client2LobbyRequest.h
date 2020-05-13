#pragma once

#include "Core/Serialization.h"

#include "CreateGameRequest.h"

namespace Vishala {

  class Client2LobbyRequest : public Serialization {
  public:
    enum class Type : int {
      Refresh, CreateGame, JoinGame
    };
    class Nothing{};
    Client2LobbyRequest();
    Client2LobbyRequest(const Client2LobbyRequest& req);
    ~Client2LobbyRequest();

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