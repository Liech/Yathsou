#include "ClientConfiguration.h"

nlohmann::json ClientConfiguration::toJson() {
  nlohmann::json result;
  result["PlayerName"]        = playerName;
  result["PlayerColor"] = playerColor;
  result["Resolution"]        = resolution;
  result["HostPort"]          = hostPort;
  result["LastGameName"]      = lastGameName;
  result["LobbyServerAdress"] = lobbyServerAdress;
  result["LobbyServerMyPort"]   = lobbyServerMyPort;
  result["LobbyServerTheirPort"]   = lobbyServerTheirPort;
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
}

Vishala::BinaryPackage ClientConfiguration::toBinary() {
  Vishala::BinaryPackage result;  
  val2bin<std::string>(result, playerName  );
  arr2bin<int,3>      (result, playerColor );
  arr2bin<int, 2>     (result, resolution  );
  val2bin<int>        (result, hostPort    );
  val2bin<std::string>(result, lastGameName);
  val2bin<std::string>(result, lobbyServerAdress);
  val2bin<int>        (result, lobbyServerMyPort);
  val2bin<int>        (result, lobbyServerTheirPort);
  return result;
}

void ClientConfiguration::fromBinary(Vishala::BinaryPackage& data) {
  playerName           = bin2val<std::string>(data);
  playerColor          = bin2arr<int,3>(data);
  resolution           = bin2arr<int, 2>(data);
  hostPort             = bin2val<int>(data);
  lastGameName         = bin2val<std::string>(data);
  lobbyServerAdress    = bin2val<std::string>(data);
  lobbyServerMyPort    = bin2val<int        >(data);
  lobbyServerTheirPort = bin2val<int        >(data);
}