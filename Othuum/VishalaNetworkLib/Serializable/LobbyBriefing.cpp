#include "LobbyBriefing.h"

#include "BinaryPackage.h"

namespace Vishala {
  BinaryPackage LobbyBriefing::toBinary()
  {
    BinaryPackage result;
    val2bin(result, playerId);
    BinaryPackage status = lobbyStatus.toBinary();
    result.add(status);
    return result;
  }

  void LobbyBriefing::fromBinary(BinaryPackage& Package)
  {
    playerId = bin2val<int>(Package);
    lobbyStatus.fromBinary(Package);
  }

  nlohmann::json LobbyBriefing::toJson()
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