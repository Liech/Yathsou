#include "ClientConfiguration.h"

nlohmann::json ClientConfiguration::toJson() {
  nlohmann::json result;
  result["PlayerName"]        = playerName;
  result["Resolution"]        = resolution;
  result["HostPort"]          = hostPort;
  result["LastGameName"]      = lastGameName;
  result["LobbyServerAdress"] = lobbyServerAdress;
  return result;
}

void ClientConfiguration::fromJson(nlohmann::json from) {
  playerName        = from["PlayerName"];
  resolution        = from["Resolution"];
  hostPort          = from["HostPort"];
  lastGameName      = from["LastGameName"];
  lobbyServerAdress = from["LobbyServerAdress"];
}

Vishala::BinaryPackage ClientConfiguration::toBinary() {
  Vishala::BinaryPackage result;  
  val2bin<std::string>(result, playerName  );
  arr2bin<int, 2>     (result, resolution  );
  val2bin<int>        (result, hostPort    );
  val2bin<std::string>(result, lastGameName);
  val2bin<std::string>(result, lobbyServerAdress);
  return result;
}

void ClientConfiguration::fromBinary(Vishala::BinaryPackage& data) {
  playerName        = bin2val<std::string>(data);
  resolution        = bin2arr<int, 2>(data);
  hostPort          = bin2val<int>(data);
  lastGameName      = bin2val<std::string>(data);
  lobbyServerAdress = bin2val<std::string>(data);
}