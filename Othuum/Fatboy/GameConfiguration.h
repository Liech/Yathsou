#pragma once

#include "VishalaNetworkLib/Core/Serialization.h"

namespace Fatboy
{
  class GameConfiguration : public Vishala::Serialization {
  public:
    static GameConfiguration& instance();

    int TicksPerSecond = 30;
    int ScreenWidth = 800;
    int ScreenHeight = 600;

    virtual nlohmann::json             toJson()                            override;
    virtual void                       fromJson(nlohmann::json)            override;
    virtual Vishala::BinaryPackage     toBinary()                          override;
    virtual void                       fromBinary(Vishala::BinaryPackage&) override;
  };
}