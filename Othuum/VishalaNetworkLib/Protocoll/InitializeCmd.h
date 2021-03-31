#pragma once

#include "VishalaNetworkLib/Core/Command.h"

namespace Vishala {
  class InitializeCmd : public ICommand {
  public:
    SERIALIZATION(InitializeCmd, "InitializeCmd")
    const std::string Name() const override { return "InitializeCmd"; }
    std::shared_ptr<Serialization> data;
    virtual void apply(Serialization& t) override;

  private:
    virtual nlohmann::json             toJson()         const     override;
    virtual void                       fromJson(nlohmann::json)   override;
    virtual BinaryPackage              toBinary()       const     override;
    virtual void                       fromBinary(BinaryPackage&) override;

  };
}