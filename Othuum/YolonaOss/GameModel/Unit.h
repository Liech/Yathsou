#pragma once

#include "VishalaNetworkLib/Core/Serialization.h"

namespace YolonaOss
{
  namespace GameModel
  {
    class Unit : public Vishala::Serialization
    {
    public:
      std::array<float, 3> position = { 0,0,0 };
      int                  owner    = 0        ; 

      virtual nlohmann::json             toJson()                   override;
      virtual void                       fromJson(nlohmann::json)   override;
      virtual Vishala::BinaryPackage     toBinary()                 override;
      virtual void                       fromBinary(Vishala::BinaryPackage&) override;
    };
  }
}