#pragma once

#include <string>
#include "Serialization.h"

namespace Vishala {
  struct ServerConfiguration : public Serialization {
    int port = 6112;

    virtual nlohmann::json          toJson()                            override;
    virtual void                    fromJson(nlohmann::json)            override;
    virtual Vishala::BinaryPackage  toBinary()                          override;
    virtual void                    fromBinary(BinaryPackage&) override;
  };
}