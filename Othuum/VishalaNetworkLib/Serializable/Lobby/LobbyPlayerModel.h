#pragma once

#include "VishalaNetworkLib/Core/Serialization.h"
#include "LobbyGame.h"
#include "LobbyPlayerModel.h"
#include <vector>

namespace Vishala {

  class LobbyPlayerModel : public Serialization {
  public:
    const std::string Name() const override { return "LobbyPlayerModel"; }

    std::string        name ;
    std::array<int, 3> color;
    size_t             id   ;

    virtual nlohmann::json             toJson()                   override;
    virtual void                       fromJson(nlohmann::json)   override;
    virtual BinaryPackage              toBinary()                 override;
    virtual void                       fromBinary(BinaryPackage&) override;
  };
}