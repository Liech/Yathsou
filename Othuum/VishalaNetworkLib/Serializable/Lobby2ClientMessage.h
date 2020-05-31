#pragma once

#include "Core/Serialization.h"
#include "Serializable/Acknowledgement.h"
#include "Serializable/LobbyBriefing.h"

namespace Vishala {

  class Lobby2ClientMessage : public Serialization {
  public:
    enum class Type : int {
      Acknowledgment, LobbyBriefing
    };
    class Nothing {};
    Lobby2ClientMessage();
    ~Lobby2ClientMessage();

    Type            type = Type::Acknowledgment;
    //union
    //{
      Acknowledgement   acknowledgment;
      LobbyBriefing     lobbyBriefing ;
      Nothing           nothing       ;
    //};

    virtual nlohmann::json             toJson()                  override;
    virtual void                       fromJson(nlohmann::json)  override;
    virtual BinaryPackage              toBinary()                override;
    virtual void                       fromBinary(BinaryPackage&) override;
  };
}