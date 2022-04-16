#pragma once

#include <string>
#include "VishalaNetworkLib/Core/Serialization.h"

namespace Uyanah {
  struct ClientConfiguration : public Vishala::Serialization {
    const std::string Name() const override { return "ClientConfiguration"; }

    int serverPort = 6212;
    int myPort     = 6213;
    std::string serverIP = "localhost";

    virtual nlohmann::json          toJson()                 const           override;
    virtual void                    fromJson(nlohmann::json)            override;
    virtual Vishala::BinaryPackage  toBinary()         const                 override;
    virtual void                    fromBinary(Vishala::BinaryPackage&) override;
  };
}