#pragma once

#include <string>
#include <vector>

#include "VishalaNetworkLib/Core/Serialization.h"


namespace Vishala {
  class CreateGameRequest : public Serialization {
  public:
    std::string                        gameName;
    
    virtual nlohmann::json             toJson()                  override;
    virtual void                       fromJson(nlohmann::json)  override;
    virtual BinaryPackage              toBinary()                override;
    virtual void                       fromBinary(BinaryPackage&) override;
  };
}