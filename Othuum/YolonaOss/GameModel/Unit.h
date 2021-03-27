#pragma once

#include "VishalaNetworkLib/Core/Serialization.h"

namespace YolonaOss
{
  namespace GameModel
  {
    class Unit : public Vishala::Serialization
    {
    public:
      const std::string Name() const override { return "Unit"; }

      std::array<float, 3> position = { 0,0,0 };
      int                  owner    = 0        ; 

      virtual nlohmann::json             toJson()        const           override;
      virtual void                       fromJson(nlohmann::json)   override;
      virtual Vishala::BinaryPackage     toBinary()     const            override;
      virtual void                       fromBinary(Vishala::BinaryPackage&) override;
    };
  }
}