#pragma once

#include <string>
#include "VishalaNetworkLib/Serialization.h"

namespace Iavish {
  struct ServerConfiguration : public Vishala::Serialization{
    int port = 6112;

    virtual nlohmann::json             toJson()                                       override;
    virtual void                       fromJson(nlohmann::json)                       override;
    virtual std::vector<unsigned char> toBinary()                                     override;
    virtual void                       fromBinary(std::vector<unsigned char>,size_t)  override;
  };
}