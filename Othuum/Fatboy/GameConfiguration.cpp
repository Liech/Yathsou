#include "GameConfiguration.h"

namespace Fatboy
{
  GameConfiguration& GameConfiguration::instance()
  {
    static GameConfiguration* g = nullptr;
    if (g == nullptr)
    {
      g = new GameConfiguration();
      g->fromJsonFile("GameConfiguration.json");
    }
    return *g;
  }

  nlohmann::json GameConfiguration::toJson() {
    nlohmann::json result;
    result["ScreenWidth"]          = ScreenWidth         ;
    result["ScreenHeight"]         = ScreenHeight        ;
    result["TicksPerSecond"] = TicksPerSecond;
    return result;
  }

  void GameConfiguration::fromJson(nlohmann::json from) {
    ScreenWidth          = from["ScreenWidth"]         ;
    ScreenHeight         = from["ScreenHeight"]        ;
    TicksPerSecond = from["TicksPerSecond"];
  }

  Vishala::BinaryPackage GameConfiguration::toBinary() {
    Vishala::BinaryPackage result;
    Vishala::BinaryPackage::val2bin<int>(result, ScreenWidth         );
    Vishala::BinaryPackage::val2bin<int>(result, ScreenHeight        );
    Vishala::BinaryPackage::val2bin<float>(result, TicksPerSecond);
    return result;
  }

  void GameConfiguration::fromBinary(Vishala::BinaryPackage& data) {
    ScreenWidth    = Vishala::BinaryPackage::bin2val<int>(data);
    ScreenHeight   = Vishala::BinaryPackage::bin2val<int>(data);
    TicksPerSecond = Vishala::BinaryPackage::bin2val<float>(data);
  }
}