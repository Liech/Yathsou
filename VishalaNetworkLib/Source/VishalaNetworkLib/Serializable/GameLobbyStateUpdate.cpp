#include "GameLobbyStateUpdate.h"

namespace Vishala {

  BinaryPackage GameLobbyStateUpdate::toBinary() const {
    BinaryPackage result;
    BinaryPackage::val2bin<std::string>(result, gameName);
    BinaryPackage::val2bin<std::string>(result, gameServerIP);
    BinaryPackage::val2bin<int>(result, gameServerPort);
    int numberOfEntries = currentPlayers.size();
    BinaryPackage::val2bin(result,numberOfEntries);
    for (int i = 0; i < numberOfEntries; i++) {
      BinaryPackage p = currentPlayers[i].toBinary();
      result.add(p);
    }
    BinaryPackage::val2bin(result, gameStart);
    return result;
  }

  void GameLobbyStateUpdate::fromBinary(BinaryPackage& Package) {
    currentPlayers.clear();

    gameName = BinaryPackage::bin2val<std::string>(Package);
    gameServerIP = BinaryPackage::bin2val<std::string>(Package);
    gameServerPort = BinaryPackage::bin2val<int>(Package);
    int numberOfEntries = BinaryPackage::bin2val<int>(Package);
    for (size_t i = 0; i < numberOfEntries; i++) {
      GameLobbyPlayer game;
      game.fromBinary(Package);
      currentPlayers.push_back(game);
    }
    gameStart = BinaryPackage::bin2val<bool>(Package);
  }

  nlohmann::json GameLobbyStateUpdate::toJson() const {
    nlohmann::json result;
    nlohmann::json arr = nlohmann::json::array();

    for (auto game : currentPlayers) {
      nlohmann::json d = game.toJson();
      arr.push_back(d);
    }
    result["CurrentPlayers"] = arr;
    result["GameName"]       = gameName;
    result["GameStart"]      = gameStart;
    result["GameServerPort"] = gameServerPort;
    result["GameServerIP"]   = gameServerIP;
    return result;
  }

  void GameLobbyStateUpdate::fromJson(nlohmann::json data) {
    currentPlayers.clear();
    for (auto game : data["CurrentPlayers"]) {
      GameLobbyPlayer g;
      g.fromJson(game);
      currentPlayers.push_back(g);
    }
    gameName       = data["GameName"];
    gameStart      = data["GameStart"];
    gameServerPort = data["GameServerPort"];
    gameServerIP   = data["GameServerIP"];
  }
}