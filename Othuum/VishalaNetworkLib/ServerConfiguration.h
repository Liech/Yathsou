#pragma once

#include <string>
#include "Serialization.h"

namespace Vishala {
  struct ServerConfiguration : public Serialization {
    int                welcomePort = 6112;
    std::array<int, 2> portRange   = { 6113,7000 };

    virtual nlohmann::json          toJson()                            override;
    virtual void                    fromJson(nlohmann::json)            override;
    virtual Vishala::BinaryPackage  toBinary()                          override;
    virtual void                    fromBinary(BinaryPackage&) override;
  };
}