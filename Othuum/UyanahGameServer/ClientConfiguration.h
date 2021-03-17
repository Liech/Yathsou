#pragma once

#include <string>
#include "VishalaNetworkLib/Core/Serialization.h"

namespace Uyanah {
  struct ClientConfiguration : public Vishala::Serialization {
    int serverPort = 6212;
    int myPort     = 6213;
    std::string serverIP = "localhost";

    virtual nlohmann::json          toJson()                            override;
    virtual void                    fromJson(nlohmann::json)            override;
    virtual Vishala::BinaryPackage  toBinary()                          override;
    virtual void                    fromBinary(Vishala::BinaryPackage&) override;
  };
}