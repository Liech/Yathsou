#pragma once

#include "Command.h"
#include "Scene.h"

namespace Uyanah {
  namespace Commands {
    class Initialize : public Command {
      SERIALIZATION(Initialize, "Initialize")
    public:
      virtual void apply(Scene&) override;
      virtual const std::string Name() const override { return "Initialize"; }

      Scene scene;

      virtual Vishala::BinaryPackage toBinary()                                  override;
      virtual void                   fromBinary(Vishala::BinaryPackage& Package) override;
      virtual nlohmann::json         toJson()                                    override;
      virtual void                   fromJson(nlohmann::json)                    override;
    };
  }
}