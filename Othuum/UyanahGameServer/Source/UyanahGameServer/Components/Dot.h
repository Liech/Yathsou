#pragma once

#include "UyanahGameServer/Component.h"
#include "IyathuumCoreLib/BaseTypes/Color.h"

namespace Uyanah {
  namespace Components {
    class Dot : public Component {
      SERIALIZATION(Dot, "Dot")
      virtual const std::string Name() const override { return "Dot"; }

      Iyathuum::Color color = Iyathuum::Color(255,255,0,255);

      virtual Vishala::BinaryPackage toBinary()        const                          override;
      virtual void                   fromBinary(Vishala::BinaryPackage& Package) override;
      virtual nlohmann::json         toJson()          const                          override;
      virtual void                   fromJson(nlohmann::json)                    override;
    };
  }
}