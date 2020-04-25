#include "LobbyGame.h"

#include "BinaryPackage.h"

namespace Vishala {

  BinaryPackage LobbyGame::toBinary(){
    BinaryPackage result;
    val2bin(result, name);
    val2bin(result, numberOfPlayers);
    val2bin(result, maxNumberOfPlayers);
    return result;
  }

  void LobbyGame::fromBinary(BinaryPackage& Package) {
    name               = bin2val<std::string>(Package);
    numberOfPlayers    = bin2val<int>(Package);
    maxNumberOfPlayers = bin2val<int>(Package);
  }

  nlohmann::json LobbyGame::toJson(){
    nlohmann::json result;
    result["Name"]               = name              ;
    result["NumberOfPlayers"]    = numberOfPlayers   ;
    result["MaxNumberOfPlayers"] = maxNumberOfPlayers;
    return result;
  }

  void LobbyGame::fromJson(nlohmann::json data){
    name               = data["Name"]              ;
    numberOfPlayers    = data["NumberOfPlayers"]   ;
    maxNumberOfPlayers = data["MaxNumberOfPlayers"];
  }
}