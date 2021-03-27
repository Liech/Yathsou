#include "ClientConfiguration.h"

nlohmann::json ClientConfiguration::toJson() const {
  nlohmann::json result;
  result["PlayerName"]             = playerName;
  result["PlayerColor"]            = playerColor;
  result["Resolution"]             = resolution;
  result["HostPort"]               = hostPort;
  result["LastGameName"]           = lastGameName;
  result["LobbyServerAdress"]      = lobbyServerAdress;
  result["LobbyServerMyPort"]      = lobbyServerMyPort;
  result["LobbyServerTheirPort"]   = lobbyServerTheirPort;
  result["GameServerPort"]         = gameServerPort;
  result["MyGameClientPort"]       = myGameClientPort;
  return result;
}

void ClientConfiguration::fromJson(nlohmann::json from) {
  playerName           = from["PlayerName"];
  playerColor          = from["PlayerColor"];
  resolution           = from["Resolution"];
  hostPort             = from["HostPort"];
  lastGameName         = from["LastGameName"];
  lobbyServerAdress    = from["LobbyServerAdress"];
  lobbyServerMyPort    = from["LobbyServerMyPort"];
  lobbyServerTheirPort = from["LobbyServerTheirPort"];
  gameServerPort       = from["GameServerPort"];
  myGameClientPort     = from["MyGameClientPort"];
}

Vishala::BinaryPackage ClientConfiguration::toBinary()const {
  Vishala::BinaryPackage result;  
  Vishala::BinaryPackage::val2bin<std::string>(result, playerName  );
  Vishala::BinaryPackage::arr2bin<int,3>      (result, playerColor );
  Vishala::BinaryPackage::arr2bin<int, 2>     (result, resolution  );
  Vishala::BinaryPackage::val2bin<int>        (result, hostPort    );
  Vishala::BinaryPackage::val2bin<std::string>(result, lastGameName);
  Vishala::BinaryPackage::val2bin<std::string>(result, lobbyServerAdress);
  Vishala::BinaryPackage::val2bin<int>        (result, lobbyServerMyPort);
  Vishala::BinaryPackage::val2bin<int>        (result, lobbyServerTheirPort);
  Vishala::BinaryPackage::val2bin<int>        (result, gameServerPort);
  Vishala::BinaryPackage::val2bin<int>        (result, myGameClientPort);
  return result;
}

void ClientConfiguration::fromBinary(Vishala::BinaryPackage& data) {
  playerName           = Vishala::BinaryPackage::bin2val<std::string>(data);
  playerColor          = Vishala::BinaryPackage::bin2arr<int,3>(data);
  resolution           = Vishala::BinaryPackage::bin2arr<int, 2>(data);
  hostPort             = Vishala::BinaryPackage::bin2val<int>(data);
  lastGameName         = Vishala::BinaryPackage::bin2val<std::string>(data);
  lobbyServerAdress    = Vishala::BinaryPackage::bin2val<std::string>(data);
  lobbyServerMyPort    = Vishala::BinaryPackage::bin2val<int        >(data);
  lobbyServerTheirPort = Vishala::BinaryPackage::bin2val<int        >(data);
  gameServerPort       = Vishala::BinaryPackage::bin2val<int        >(data);
  myGameClientPort     = Vishala::BinaryPackage::bin2val<int        >(data);
}