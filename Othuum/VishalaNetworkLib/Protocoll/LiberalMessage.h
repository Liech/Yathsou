#pragma once

#include "VishalaNetworkLib/Core/Serialization.h"

namespace Vishala {
  class ICommand;

  struct LiberalMessage : Serialization {
  public:
    const int clientReportIntervall = 120;

    const std::string Name() const override { return "LiberalMessage"; }
    enum class Type {
      Command, Start, Pause, Ready, Initialization, ClientReport
    };

    LiberalMessage::Type      type    = LiberalMessage::Type::Start;
    size_t                    tick    = 0;
    std::shared_ptr<ICommand> command = nullptr;

    virtual nlohmann::json             toJson()         const     override;
    virtual void                       fromJson(nlohmann::json)   override;
    virtual BinaryPackage              toBinary()       const     override;
    virtual void                       fromBinary(BinaryPackage&) override;
  };
}