#include "LobbyStateUpdate.h"

namespace Vishala {

  BinaryPackage LobbyStateUpdate::toBinary() {
    BinaryPackage result;
    int numberOfEntries = openGames.size();    
    val2bin(result,numberOfEntries);
    for (int i = 0; i < numberOfEntries; i++) {
      BinaryPackage p = openGames[i].toBinary();
      result.add(p);
    }
    return result;
  }

  void LobbyStateUpdate::fromBinary(BinaryPackage& Package) {
    openGames.clear();
    int numberOfEntries = bin2val<int>(Package);
    for (size_t i = 0; i < numberOfEntries; i++) {
      LobbyGame game;
      game.fromBinary(Package);
      openGames.push_back(game);
    }
  }

  nlohmann::json LobbyStateUpdate::toJson() {
    nlohmann::json result;
    nlohmann::json arr = nlohmann::json::array();

    for (auto game : openGames) {
      nlohmann::json d = game.toJson();
      arr.push_back(d);
    }
    result["OpenGames"] = arr;
    return result;
  }

  void LobbyStateUpdate::fromJson(nlohmann::json data) {
    openGames.clear();
    for (auto game : data["OpenGames"]) {
      LobbyGame g;
      g.fromJson(game);
      openGames.push_back(g);
    }
  }
}