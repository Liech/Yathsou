#pragma once

#include <string>

#include "VishalaNetworkLib/Core/Serialization.h"

namespace Vishala {
  struct Message : Serialization{
    const std::string Name() const override { return "Message"; }
    int playerID;
    int message ;
    
    virtual nlohmann::json             toJson()         const         override;
    virtual void                       fromJson(nlohmann::json)  override;
    virtual BinaryPackage              toBinary()       const         override;
    virtual void                       fromBinary(BinaryPackage&) override;
  };
}