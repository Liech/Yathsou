#pragma once

#include <string>
#include <vector>

#include "Core/Serialization.h"


namespace Vishala {
  struct JoinGameRequest : public Serialization {
  public:
    const std::string Name() const override { return "JoinGameRequest"; }
    int gameID;
    
    virtual nlohmann::json             toJson()            const       override;
    virtual void                       fromJson(nlohmann::json)   override;
    virtual BinaryPackage              toBinary()         const        override;
    virtual void                       fromBinary(BinaryPackage&) override;
  };
}