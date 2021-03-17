#pragma once

#include <string>
#include "VishalaNetworkLib/Core/Serialization.h"

namespace Uyanah {
  struct DedicatedServerConfiguration : public Vishala::Serialization {
    int welcomePort = 6212;
    
    virtual nlohmann::json          toJson()                            override;
    virtual void                    fromJson(nlohmann::json)            override;
    virtual Vishala::BinaryPackage  toBinary()                          override;
    virtual void                    fromBinary(Vishala::BinaryPackage&) override;
  };
}