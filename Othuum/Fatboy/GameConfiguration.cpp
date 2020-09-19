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
    val2bin<int>(result, ScreenWidth         );
    val2bin<int>(result, ScreenHeight        );
    val2bin<int>(result, TicksPerSecond);
    return result;
  }

  void GameConfiguration::fromBinary(Vishala::BinaryPackage& data) {
    ScreenWidth          = bin2val<int>(data);
    ScreenHeight         = bin2val<int>(data);
    TicksPerSecond = bin2val<int>(data);
  }
}