#pragma once

#include <string>

#include "VishalaNetworkLib/Serialization.h"

namespace Vishala {
  struct Message : Serialization{
    int playerID;
    int message ;
    
    virtual nlohmann::json             toJson()                                                override;
    virtual void                       fromJson(nlohmann::json)                                override;
    virtual std::vector<unsigned char> toBinary()                                              override;
    virtual void                       fromBinary(std::vector<unsigned char>, size_t position) override;
  };
}