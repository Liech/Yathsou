#include "Unit.h"

namespace YolonaOss
{
  namespace GameModel
  {
    nlohmann::json Unit::toJson() {
      nlohmann::json result;
      result["Position"] = position;
      result["Owner"]    = owner   ;
      return result;
    }

    void Unit::fromJson(nlohmann::json from) {
      position = from["Position"];
      owner    = from["Owner"]   ;
    }

    Vishala::BinaryPackage Unit::toBinary() {
      Vishala::BinaryPackage result;
      Vishala::BinaryPackage::arr2bin(result, position);
      Vishala::BinaryPackage::val2bin(result, owner   );
      return result;
    }

    void Unit::fromBinary(Vishala::BinaryPackage& data) {
      position = Vishala::BinaryPackage::bin2arr<float,3>(data);
      owner    = Vishala::BinaryPackage::bin2val<int>    (data);
    }
  }
}