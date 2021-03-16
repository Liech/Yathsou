#include "GameLobbyStateUpdate.h"

namespace Vishala {

  BinaryPackage GameLobbyStateUpdate::toBinary() {
    BinaryPackage result;
    val2bin<std::string>(result,gameName);
    int numberOfEntries = currentPlayers.size();
    val2bin(result,numberOfEntries);
    for (int i = 0; i < numberOfEntries; i++) {
      BinaryPackage p = currentPlayers[i].toBinary();
      result.add(p);
    }
    val2bin(result, gameStart);
    return result;
  }

  void GameLobbyStateUpdate::fromBinary(BinaryPackage& Package) {
    currentPlayers.clear();

    gameName = bin2val<std::string>(Package);
    int numberOfEntries = bin2val<int>(Package);
    for (size_t i = 0; i < numberOfEntries; i++) {
      GameLobbyPlayer game;
      game.fromBinary(Package);
      currentPlayers.push_back(game);
    }
    gameStart = bin2val<bool>(Package);
  }

  nlohmann::json GameLobbyStateUpdate::toJson() {
    nlohmann::json result;
    nlohmann::json arr = nlohmann::json::array();

    for (auto game : currentPlayers) {
      nlohmann::json d = game.toJson();
      arr.push_back(d);
    }
    result["CurrentPlayers"] = arr;
    result["GameName"]       = gameName;
    result["GameStart"]      = gameStart;
    return result;
  }

  void GameLobbyStateUpdate::fromJson(nlohmann::json data) {
    currentPlayers.clear();
    for (auto game : data["CurrentPlayers"]) {
      GameLobbyPlayer g;
      g.fromJson(game);
      currentPlayers.push_back(g);
    }
    gameName  = data["GameName"];
    gameStart = data["GameStart"];
  }
}