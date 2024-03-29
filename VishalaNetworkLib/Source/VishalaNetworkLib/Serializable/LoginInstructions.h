#pragma once

#include "Core/Serialization.h"

namespace Vishala {
  class LoginInstructions : public Serialization {
  public:
    const std::string Name() const override { return "LoginInstructions"; }
    std::string ip  ;
    int         port = 0;

    virtual BinaryPackage toBinary()const override;
    virtual void fromBinary(BinaryPackage& Package) override;
    virtual nlohmann::json toJson()const override;
    virtual void fromJson(nlohmann::json) override;
  };
}