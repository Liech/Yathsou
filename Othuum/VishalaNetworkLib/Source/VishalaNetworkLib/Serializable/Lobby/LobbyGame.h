#pragma once

#include <string>
#include <vector>

#include "Core/Serialization.h"

namespace Vishala {
  class LobbyGame : public Serialization {
  public:
    const std::string Name() const override { return "LobbyGame"; }

    std::string name              ;
    int         numberOfPlayers   ;
    int         maxNumberOfPlayers;
    int         gameID            ;

    virtual BinaryPackage toBinary()       const         override;
    virtual void fromBinary(BinaryPackage& Package) override;
    virtual nlohmann::json toJson()   const              override;
    virtual void fromJson(nlohmann::json)           override;
  };
}