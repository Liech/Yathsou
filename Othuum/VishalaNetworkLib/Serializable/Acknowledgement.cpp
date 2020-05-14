#include "Acknowledgement.h"

namespace Vishala {
  nlohmann::json Acknowledgement::toJson() {
    nlohmann::json result;
    int number = (int)type;
    result["Type"] = number;
    return result;
  }

  void Acknowledgement::fromJson(nlohmann::json from) {
    int number = from["Type"];
    type = (Acknowledgement::Type)number;
  }

  BinaryPackage Acknowledgement::toBinary() {
    BinaryPackage result;
    int number = (int)type;
    val2bin<int>(result, number);
    return result;
  }

  void Acknowledgement::fromBinary(BinaryPackage& data) {    
    int number = bin2val<int>(data);
    type = (Acknowledgement::Type)number;
  }
}