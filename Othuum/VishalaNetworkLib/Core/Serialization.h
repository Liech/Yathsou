#pragma once

#include <map>
#include <string>
#include <set>

#include "VishalaNetworkLib/lib/json.hpp"

#include "BinaryPackage.h"

namespace Vishala {
  struct Serialization {
    virtual BinaryPackage              toBinary() = 0;
    virtual void                       fromBinary(BinaryPackage& Package) = 0;
    virtual nlohmann::json             toJson() = 0;
    virtual void                       fromJson(nlohmann::json) = 0;
            void                       toJsonFile(std::string filename);
            void                       fromJsonFile(std::string filename);
            void                       toBinFile(std::string filename);
            void                       fromBinFile(std::string filename); 
  };
}