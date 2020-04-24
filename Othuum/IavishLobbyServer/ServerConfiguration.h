#pragma once

#include <string>
#include "VishalaNetworkLib/Serialization.h"

namespace Iavish {
  struct ServerConfiguration : public Vishala::Serialization{
    int port = 6112;

    virtual nlohmann::json          toJson()                                       override;
    virtual void                    fromJson(nlohmann::json)                       override;
    virtual Vishala::BinaryPackage  toBinary()                                     override;
    virtual void                    fromBinary(Vishala::BinaryPackage&)  override;
  };
}