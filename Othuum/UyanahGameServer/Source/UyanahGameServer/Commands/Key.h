#pragma once

#include "VishalaNetworkLib/Core/Command.h"
#include "IyathuumCoreLib/BaseTypes/Keys.h"
#include "UyanahGameServer/Scene.h"

namespace Uyanah {
  namespace Commands {
    class KeyCmd : public Vishala::Command<Scene> {
      SERIALIZATION(KeyCmd, "KeyCmd")
    public:
      virtual void _apply(Scene&) override;
      virtual const std::string Name() const override { return "KeyCmd"; }

      Iyathuum::Key       key      = Iyathuum::Key::KEY_SPACE;
      Iyathuum::KeyStatus status   = Iyathuum::KeyStatus::PRESS;
      size_t              targetID = 0;

      virtual Vishala::BinaryPackage toBinary()             const                     override;
      virtual void                   fromBinary(Vishala::BinaryPackage& Package) override;
      virtual nlohmann::json         toJson()               const                     override;
      virtual void                   fromJson(nlohmann::json)                    override;

    };
  }
}