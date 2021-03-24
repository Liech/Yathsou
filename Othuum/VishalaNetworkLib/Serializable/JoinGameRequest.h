#pragma once

#include <string>
#include <vector>

#include "VishalaNetworkLib/Core/Serialization.h"


namespace Vishala {
  struct JoinGameRequest : public Serialization {
  public:
    const std::string Name() const override { return "JoinGameRequest"; }
    int gameID;
    
    virtual nlohmann::json             toJson()                  override;
    virtual void                       fromJson(nlohmann::json)  override;
    virtual BinaryPackage              toBinary()                override;
    virtual void                       fromBinary(BinaryPackage&) override;
  };
}