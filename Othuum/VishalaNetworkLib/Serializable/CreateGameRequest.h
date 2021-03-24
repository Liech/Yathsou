#pragma once

#include <string>
#include <vector>

#include "VishalaNetworkLib/Core/Serialization.h"


namespace Vishala {
  struct CreateGameRequest : public Serialization {
  public:
    const std::string Name() const override { return "CreateGameRequest"; }
    std::string                        gameName;
    int                                serverPort = 6333;
    
    virtual nlohmann::json             toJson()                  override;
    virtual void                       fromJson(nlohmann::json)  override;
    virtual BinaryPackage              toBinary()                override;
    virtual void                       fromBinary(BinaryPackage&) override;
  };
}