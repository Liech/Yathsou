#include "LobbyGame.h"

#include "Core/BinaryPackage.h"

namespace Vishala {

  BinaryPackage LobbyGame::toBinary(){
    BinaryPackage result;
    BinaryPackage::val2bin(result, name);
    BinaryPackage::val2bin(result, numberOfPlayers);
    BinaryPackage::val2bin(result, maxNumberOfPlayers);
    BinaryPackage::val2bin(result, gameID);
    return result;
  }

  void LobbyGame::fromBinary(BinaryPackage& Package) {
    name               = BinaryPackage::bin2val<std::string>(Package);
    numberOfPlayers    = BinaryPackage::bin2val<int>(Package);
    maxNumberOfPlayers = BinaryPackage::bin2val<int>(Package);
    gameID             = BinaryPackage::bin2val<int>(Package);
  }

  nlohmann::json LobbyGame::toJson(){
    nlohmann::json result;
    result["Name"]               = name              ;
    result["NumberOfPlayers"]    = numberOfPlayers   ;
    result["MaxNumberOfPlayers"] = maxNumberOfPlayers;
    result["GameID"]             = gameID;
    return result;
  }

  void LobbyGame::fromJson(nlohmann::json data){
    name               = data["Name"]              ;
    numberOfPlayers    = data["NumberOfPlayers"]   ;
    maxNumberOfPlayers = data["MaxNumberOfPlayers"];
    gameID             = data["GameID"];
  }
}