#include "LobbyModel.h"

namespace Vishala {

  BinaryPackage LobbyModel::toBinary() {
    BinaryPackage result;
    int numberOfGames = openGames.size();
    BinaryPackage::val2bin(result, numberOfGames);
    for (size_t i = 0; i < numberOfGames; i++)
      result.add(openGames[i].toBinary());

    int numberOfPlayers = players.size();
    BinaryPackage::val2bin(result, numberOfPlayers);
    for (size_t i = 0; i < numberOfPlayers; i++)
      result.add(players[i].toBinary());

    int numberOfRequests = openRequests.size();
    BinaryPackage::val2bin(result, numberOfRequests);
    for (size_t i = 0; i < numberOfRequests; i++)
      result.add(openRequests[i].toBinary());

    BinaryPackage::val2bin(result, nextPlayerNumber);
    BinaryPackage::val2bin(result, nextGameNumber);
    return result;
  }

  void LobbyModel::fromBinary(BinaryPackage& Package) {
    openGames.clear();
    players.clear();
    openRequests.clear();

    int numberOfGames = BinaryPackage::bin2val<int>(Package);
    for (size_t i = 0; i < numberOfGames; i++) {
      LobbyGame game;
      game.fromBinary(Package);
      openGames.push_back(game);
    }

    int numberOfPlayers = BinaryPackage::bin2val<int>(Package);
    for (size_t i = 0; i < numberOfPlayers; i++) {
      LobbyPlayerModel player;
      player.fromBinary(Package);
      players.push_back(player);
    }

    int numberOfRequests = BinaryPackage::bin2val<int>(Package);
    for (size_t i = 0; i < numberOfRequests; i++) {
      OpenLobbyRequest request;
      request.fromBinary(Package);
      openRequests.push_back(request);
    }

    nextPlayerNumber = BinaryPackage::bin2val<size_t>(Package);
    nextGameNumber = BinaryPackage::bin2val<size_t>(Package);
  }

  nlohmann::json LobbyModel::toJson() {
    nlohmann::json result;

    nlohmann::json games = nlohmann::json::array();
    for (auto game : openGames) {
      nlohmann::json d = game.toJson();
      games.push_back(d);
    }
    result["OpenGames"] = games;

    nlohmann::json jsonPlayers = nlohmann::json::array();
    for (auto p : players) {
      nlohmann::json d = p.toJson();
      jsonPlayers.push_back(d);
    }
    result["Player"] = jsonPlayers;

    nlohmann::json jsonRequests = nlohmann::json::array();
    for (auto p : openRequests) {
      nlohmann::json d = p.toJson();
      jsonRequests.push_back(d);
    }
    result["OpenRequests"] = jsonPlayers;
    result["NextPlayerNumber"] = nextPlayerNumber;
    result["NextGameNumber"]   = nextGameNumber;

    return result;
  }

  void LobbyModel::fromJson(nlohmann::json data) {
    openGames.clear();
    for (auto game : data["OpenGames"]) {
      LobbyGame g;
      g.fromJson(game);
      openGames.push_back(g);
    }   

    players.clear();
    for (auto game : data["Player"]) {
      LobbyPlayerModel g;
      g.fromJson(game);
      players.push_back(g);
    }

    openRequests.clear();
    for (auto game : data["OpenRequests"]) {
      OpenLobbyRequest g;
      g.fromJson(game);
      openRequests.push_back(g);
    }

    nextPlayerNumber = data["NextPlayerNumber"];
    nextGameNumber = data["NextGameNumber"];
  }
}