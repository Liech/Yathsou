#pragma once

#include "VishalaNetworkLib/Core/Serialization.h"

namespace Fatboy
{
  class GameConfiguration : public Vishala::Serialization {
  public:
    const std::string Name() const override { return "GameConfiguration"; }
    static GameConfiguration& instance();

    float TicksPerSecond = 60;
    int   ScreenWidth    = 800;
    int   ScreenHeight   = 600;

    virtual nlohmann::json             toJson()            const                override;
    virtual void                       fromJson(nlohmann::json)            override;
    virtual Vishala::BinaryPackage     toBinary()          const                override;
    virtual void                       fromBinary(Vishala::BinaryPackage&) override;
  };
}