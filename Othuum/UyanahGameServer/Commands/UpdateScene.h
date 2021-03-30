#pragma once

#include "VishalaNetworkLib/Core/Command.h"
#include "IyathuumCoreLib/BaseTypes/Keys.h"
#include "UyanahGameServer/Scene.h"

namespace Uyanah {
  namespace Commands {
    class UpdateScene : public Vishala::Command<Scene> {
      SERIALIZATION(UpdateScene, "UpdateScene")
    public:
      virtual void _apply(Scene&) override;
      virtual const std::string Name() const override { return "UpdateScene"; }

      virtual Vishala::BinaryPackage toBinary()             const                     override;
      virtual void                   fromBinary(Vishala::BinaryPackage& Package) override;
      virtual nlohmann::json         toJson()               const                     override;
      virtual void                   fromJson(nlohmann::json)                    override;

    };
  }
}