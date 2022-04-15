#pragma once

#include <string>

#include "Core/Serialization.h"

namespace Vishala {
  struct Acknowledgement : Serialization {
  public:
    const std::string Name() const override { return "Acknowledgement"; }
    enum class Type {
      GameHosted, GameJoined
    };

    Acknowledgement::Type type;

    virtual nlohmann::json             toJson()         const     override;
    virtual void                       fromJson(nlohmann::json)   override;
    virtual BinaryPackage              toBinary()       const     override;
    virtual void                       fromBinary(BinaryPackage&) override;
  };
}