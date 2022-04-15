#pragma once

#include <string>
#include "Core/Serialization.h"

namespace Vishala {
  struct ServerConfiguration : public Serialization {
    const std::string Name() const override { return "ServerConfiguration"; }
    
    int                welcomePort = 6112;
    std::array<int, 2> portRange   = { 6113,7000 };

    virtual nlohmann::json          toJson()              const              override;
    virtual void                    fromJson(nlohmann::json)            override;
    virtual Vishala::BinaryPackage  toBinary()           const               override;
    virtual void                    fromBinary(BinaryPackage&) override;
  };
}