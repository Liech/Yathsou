#pragma once

#include <string>

#include "VishalaNetworkLib/Core/Serialization.h"

namespace Vishala {
  struct Message : Serialization{
    int playerID;
    int message ;
    
    virtual nlohmann::json             toJson()                  override;
    virtual void                       fromJson(nlohmann::json)  override;
    virtual BinaryPackage              toBinary()                override;
    virtual void                       fromBinary(BinaryPackage&) override;
  };
}