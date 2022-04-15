#include "GameLobbyPlayer.h"

namespace Vishala {

  BinaryPackage GameLobbyPlayer::toBinary() const{
    BinaryPackage result;
    result.add(lobbyIdentification.toBinary());
    return result;
  }

  void GameLobbyPlayer::fromBinary(BinaryPackage& Package) {
    lobbyIdentification.fromBinary(Package);
  }

  nlohmann::json GameLobbyPlayer::toJson() const{
    nlohmann::json result;
    result["LobbyPlayer"] = lobbyIdentification.toJson();
    return result;
  }

  void GameLobbyPlayer::fromJson(nlohmann::json data) {
    lobbyIdentification.fromJson(data["LobbyPlayer"]);
  }
}