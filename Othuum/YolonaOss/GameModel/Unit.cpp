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
      arr2bin(result, position);
      val2bin(result, owner   );
      return result;
    }

    void Unit::fromBinary(Vishala::BinaryPackage& data) {
      position = bin2arr<float,3>(data);
      owner    = bin2val<int>    (data);
    }
  }
}