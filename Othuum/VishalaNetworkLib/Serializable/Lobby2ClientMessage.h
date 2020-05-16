#pragma once

#include "Core/Serialization.h"
#include "Serializable/Acknowledgement.h"

namespace Vishala {

  class Lobby2ClientMessage : public Serialization {
  public:
    enum class Type : int {
      Acknowledgment
    };
    class Nothing {};
    Lobby2ClientMessage();
    Lobby2ClientMessage(const Lobby2ClientMessage& req);
    ~Lobby2ClientMessage();

    Type            type = Type::Acknowledgment;
    union
    {
      Acknowledgement   acknowledgment;
      Nothing           nothing;
    };

    virtual nlohmann::json             toJson()                  override;
    virtual void                       fromJson(nlohmann::json)  override;
    virtual BinaryPackage              toBinary()                override;
    virtual void                       fromBinary(BinaryPackage&) override;
  };
}