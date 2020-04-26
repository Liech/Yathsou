#pragma once

#include <string>
#include <array>

#include "Serialization.h"

namespace Vishala {
  class SelfBriefing : public Serialization{
  public:
    std::string        name ;
    std::array<int, 3> color;

    virtual BinaryPackage  toBinary()                         override;
    virtual void           fromBinary(BinaryPackage& Package) override;
    virtual nlohmann::json toJson()                           override;
    virtual void           fromJson(nlohmann::json)           override;
  };
}