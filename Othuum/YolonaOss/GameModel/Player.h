#pragma once

#include "VishalaNetworkLib/Core/Serialization.h"

namespace YolonaOss
{
  namespace GameModel
  {
    class Player : public Vishala::Serialization
    {
    public:
      const std::string Name() const override { return "Player"; }
      std::string name;


      virtual nlohmann::json             toJson()                   override;
      virtual void                       fromJson(nlohmann::json)   override;
      virtual Vishala::BinaryPackage     toBinary()                 override;
      virtual void                       fromBinary(Vishala::BinaryPackage&) override;
    };
  }
}