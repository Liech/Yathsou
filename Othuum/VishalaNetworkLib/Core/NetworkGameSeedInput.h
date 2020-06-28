#pragma once

#include "VishalaNetworkLib/Core/Serialization.h"

/*
  The GameSeeds goal is to get a list of ip+port & info packages and make sure that the seed is connected to all seeds on the other side
  If the connection is lost it reconnects them
  Somehow the Peer2Peer central hub.
  The MainMenu should spit one out, which can be used to start a game
  It could be generated otherwise. Maybe even automated for cloud based ai
  Im not sure about the name. Something like "ConnectionManager" sounds lame. The primary job is to be the general core part of a startGame invocation
*/
namespace Vishala {
    class NetworkGameSeedInput : public Serialization {
    public:
      struct Address {
        std::string IP  ;
        int         port;
      };
      int                  ownPort          = 6551;
      int                  numberOfChannels = 1   ;
      std::vector<Address> targets                ;

      virtual BinaryPackage toBinary()                override;
      virtual void fromBinary(BinaryPackage& Package) override;
      virtual nlohmann::json toJson()                 override;
      virtual void fromJson(nlohmann::json)           override;
    };
}