#include "LobbyBriefing.h"

#include "Core/BinaryPackage.h"

namespace Vishala {
  BinaryPackage LobbyBriefing::toBinary()const
  {
    BinaryPackage result;
    BinaryPackage::val2bin(result, playerId);
    BinaryPackage status = lobbyStatus.toBinary();
    result.add(status);
    return result;
  }

  void LobbyBriefing::fromBinary(BinaryPackage& Package)
  {
    playerId = BinaryPackage::bin2val<int>(Package);
    lobbyStatus.fromBinary(Package);
  }

  nlohmann::json LobbyBriefing::toJson()const
  {
    nlohmann::json result;
    result["PlayerID"] = playerId;
    result["LobbyStatus"] = lobbyStatus.toJson();
    return result;
  }

  void LobbyBriefing::fromJson(nlohmann::json data)
  {
    playerId    = data["PlayerID"];
    LobbyStateUpdate up;
    up.fromJson(data["LobbyStatus"]);
    lobbyStatus = up;
  }
}