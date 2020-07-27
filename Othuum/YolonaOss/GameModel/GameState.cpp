#include "GameState.h"

#include "Player.h"
#include "Unit.h"

namespace YolonaOss
{
  namespace GameModel
  {
    nlohmann::json GameState::toJson() {
      nlohmann::json result;
      nlohmann::json arr = nlohmann::json::array();
      for(auto p : players)
        arr.push_back({ p.first,p.second.toJson() });
      result["Players"] = arr;

      arr = nlohmann::json::array();
      for (auto p : units)
        arr.push_back({ p.first,p.second.toJson() });
      result["Units"] = arr;
      return result;
    }

    void GameState::fromJson(nlohmann::json from) {
      players.clear();
      for (auto p : from["Players"]) {
        GameModel::Player pl;
        pl.fromJson(p[1]);
        players[p[0]] = pl;
      }

      units.clear();
      for (auto p : from["Units"]) {
        GameModel::Unit pl;
        pl.fromJson(p[1]);
        units[p[0]] = pl;
      }
    }

    Vishala::BinaryPackage GameState::toBinary() {
      Vishala::BinaryPackage result;
      map2bin(result, players);
      map2bin(result, units  );
      return result;
    }

    void GameState::fromBinary(Vishala::BinaryPackage& data) {
      players = bin2map<int,GameModel::Player>(data);
      units   = bin2map<int,GameModel::Unit  >(data);
    }
  }
}