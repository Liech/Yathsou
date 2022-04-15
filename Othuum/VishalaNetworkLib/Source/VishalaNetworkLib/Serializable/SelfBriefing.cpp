#include "SelfBriefing.h"

namespace Vishala {
  BinaryPackage  SelfBriefing::toBinary()const {
    BinaryPackage result;
    BinaryPackage::val2bin(result, name );
    BinaryPackage::arr2bin<int,3>(result, color); 
    return result;
  }

  void SelfBriefing::fromBinary(BinaryPackage& Package){
    name  = BinaryPackage::bin2val<std::string>(Package);
    color = BinaryPackage::bin2arr<int, 3>(Package);
  }

  nlohmann::json SelfBriefing::toJson()const {
    nlohmann::json result;
    result["Name"] = name;
    result["Color"] = color;
    return result;
  }

  void SelfBriefing::fromJson(nlohmann::json data){
    name  = data["Name"];
    color = data["Color"];
  }
}