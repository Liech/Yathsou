#pragma once

#include "VishalaNetworkLib/Core/Serialization.h"

namespace YolonaOss
{
  namespace GameModel
  {
    class Player;
    class Unit;

    class GameState : public Vishala::Serialization
    {
    public:
      std::map<int, GameModel::Player> players;
      std::map<int, GameModel::Unit  > units  ;

      virtual nlohmann::json             toJson()      const                      override;
      virtual void                       fromJson(nlohmann::json)            override;
      virtual Vishala::BinaryPackage     toBinary()     const                     override;
      virtual void                       fromBinary(Vishala::BinaryPackage&) override;
    };
  }
}