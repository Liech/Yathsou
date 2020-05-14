#pragma once

#include <string>

#include "VishalaNetworkLib/Core/Serialization.h"

namespace Vishala {
  struct Acknowledgement : Serialization {
  public:
    enum class Type {
      GameHosted
    };

    Acknowledgement::Type type;

    virtual nlohmann::json             toJson()                   override;
    virtual void                       fromJson(nlohmann::json)   override;
    virtual BinaryPackage              toBinary()                 override;
    virtual void                       fromBinary(BinaryPackage&) override;
  };
}