#pragma once

#include <string>
#include <array>

#include "Core/Serialization.h"

namespace Vishala {
  class SelfBriefing : public Serialization{
  public:
    const std::string Name() const override { return "SelfBriefing"; }

    std::string        name ;
    std::array<int, 3> color = { 0,0,0 };

    virtual BinaryPackage  toBinary()              const           override;
    virtual void           fromBinary(BinaryPackage& Package) override;
    virtual nlohmann::json toJson()               const            override;
    virtual void           fromJson(nlohmann::json)           override;
  };
}