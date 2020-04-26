#include "SelfBriefing.h"

namespace Vishala {
  BinaryPackage  SelfBriefing::toBinary(){
    BinaryPackage result;
    val2bin(result, name );
    arr2bin(result, color);
    return result;
  }

  void SelfBriefing::fromBinary(BinaryPackage& Package){
    name  = bin2val<std::string>(Package);
    color = bin2arr<int, 3>(Package);
  }

  nlohmann::json SelfBriefing::toJson(){
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