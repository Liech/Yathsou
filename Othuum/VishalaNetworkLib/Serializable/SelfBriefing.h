#pragma once

#include <string>
#include <array>

#include "VishalaNetworkLib/Core/Serialization.h"

namespace Vishala {
  class SelfBriefing : public Serialization{
  public:
    const std::string Name() const override { return "SelfBriefing"; }

    std::string        name ;
    std::array<int, 3> color = { 0,0,0 };

    virtual BinaryPackage  toBinary()                         override;
    virtual void           fromBinary(BinaryPackage& Package) override;
    virtual nlohmann::json toJson()                           override;
    virtual void           fromJson(nlohmann::json)           override;
  };
}