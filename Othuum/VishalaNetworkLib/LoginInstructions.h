#pragma once

#include "Serialization.h"

namespace Vishala {
  class LoginInstructions : public Serialization {
  public:
    std::string ip  ;
    int         port;

    virtual BinaryPackage toBinary() override;
    virtual void fromBinary(BinaryPackage& Package) override;
    virtual nlohmann::json toJson() override;
    virtual void fromJson(nlohmann::json) override;
  };
}