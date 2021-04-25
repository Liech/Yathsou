#include "EyeOfRhianneConfiguration.h"

nlohmann::json EyeOfRhianneConfiguration::toJson() const {
  nlohmann::json result;
  result["ScreenWidth"]  = ScreenWidth ;
  result["ScreenHeight"] = ScreenHeight;
  result["AssetPath"]    = AssetPath   ;
  result["ShowFPS"]      = ShowFPS     ;
  return result;
}

void EyeOfRhianneConfiguration::fromJson(nlohmann::json from) {
  ScreenWidth  = from["ScreenWidth"] ;
  ScreenHeight = from["ScreenHeight"];
  AssetPath    = from["AssetPath"];
  ShowFPS      = from["ShowFPS"];
}

Vishala::BinaryPackage EyeOfRhianneConfiguration::toBinary()const {
  Vishala::BinaryPackage result;
  Vishala::BinaryPackage::val2bin<int        >(result, ScreenWidth );
  Vishala::BinaryPackage::val2bin<int        >(result, ScreenHeight);
  Vishala::BinaryPackage::val2bin<bool       >(result, ShowFPS     );
  Vishala::BinaryPackage::val2bin<std::string>(result, AssetPath   );
  return result;
}

void EyeOfRhianneConfiguration::fromBinary(Vishala::BinaryPackage& data) {
  ScreenWidth  = Vishala::BinaryPackage::bin2val<int        >(data);
  ScreenHeight = Vishala::BinaryPackage::bin2val<int        >(data);
  ShowFPS      = Vishala::BinaryPackage::bin2val<bool       >(data);
  AssetPath    = Vishala::BinaryPackage::bin2val<std::string>(data);
}