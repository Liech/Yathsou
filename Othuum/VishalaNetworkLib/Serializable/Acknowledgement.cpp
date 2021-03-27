#include "Acknowledgement.h"

namespace Vishala {
  nlohmann::json Acknowledgement::toJson() const {
    nlohmann::json result;
    int number = (int)type;
    result["Type"] = number;
    return result;
  }

  void Acknowledgement::fromJson(nlohmann::json from) {
    int number = from["Type"];
    type = (Acknowledgement::Type)number;
  }

  BinaryPackage Acknowledgement::toBinary() const{
    BinaryPackage result;
    int number = (int)type;
    BinaryPackage::val2bin<int>(result, number);
    return result;
  }

  void Acknowledgement::fromBinary(BinaryPackage& data) {    
    int number = BinaryPackage::bin2val<int>(data);
    type = (Acknowledgement::Type)number;
  }
}