#pragma once

#include <memory>
#include "VishalaNetworkLib/Core/Command.h"
#include "UyanahGameServer/Scene.h"
namespace Vishala {
  class BinaryPackage;
}


class InitializeCmd : public Vishala::Command<Uyanah::Scene> {
public:
  SERIALIZATION(InitializeCmd, "InitializeCmd")

  const std::string Name() const override { return "InitializeCmd"; }
  Uyanah::Scene data;
  virtual void _apply(Uyanah::Scene& t) override;

private:
  virtual nlohmann::json             toJson()         const     override;
  virtual void                       fromJson(nlohmann::json)   override;
  virtual Vishala::BinaryPackage     toBinary()       const     override;
  virtual void                       fromBinary(Vishala::BinaryPackage&) override;

};
